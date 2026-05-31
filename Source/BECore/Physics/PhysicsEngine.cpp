
#include "PhysicsEngine.h"

#include <Jolt/Jolt.h>

#include <glm/gtc/quaternion.hpp>

#include "BECore/Math/Location.h"
// Jolt requires Jolt.h to be included before other Jolt headers
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#include <cmath>
#include <thread>

#include "BECore/logger.h"

// Jolt expects the application to provide an assert handler when asserts are enabled.
// In Debug, Jolt forces JPH_ENABLE_ASSERTS on (see Jolt/Core/IssueReporting.h), so we must
// define this callback variable in exactly one translation unit.
#ifdef JPH_ENABLE_ASSERTS
static bool BeJoltAssertFailed(const char *expression, const char *message, const char *file, JPH::uint line)
{
    if (message != nullptr)
    {
        LOG("Jolt assert failed: %s | %s (%s:%u)", expression, message, file, static_cast<unsigned>(line));
    } else
    {
        LOG("Jolt assert failed: %s (%s:%u)", expression, file, static_cast<unsigned>(line));
    }
    return true; // Request a breakpoint
}

JPH_EXPORT JPH::AssertFailedFunction JPH::AssertFailed = &BeJoltAssertFailed;
#endif

struct PhysicsEngine::Impl
{
    JPH::PhysicsSystem m_physicsSystem;
    JPH::TempAllocator *m_tempAllocator = nullptr;
    JPH::JobSystem *m_jobSystem = nullptr;
    JPH::BodyInterface *m_bodyInterface = nullptr;

    // Keep layer/filter objects alive for the lifetime of the physics system
    JPH::BroadPhaseLayerInterface *m_broadPhaseLayerInterface = nullptr;
    JPH::ObjectVsBroadPhaseLayerFilter *m_objectVsBroadPhaseFilter = nullptr;
    JPH::ObjectLayerPairFilter *m_objectLayerPairFilter = nullptr;
};

static PhysicsEngine *_currentPhysicsEngine = nullptr;

PhysicsEngine::PhysicsEngine()
    : m_impl(std::make_unique<Impl>())
{
    _currentPhysicsEngine = this;
}

PhysicsEngine::~PhysicsEngine()
{
    // Clean up Jolt resources
    if (m_impl)
    {
        // Delete filters / interfaces
        delete m_impl->m_broadPhaseLayerInterface;
        m_impl->m_broadPhaseLayerInterface = nullptr;
        delete m_impl->m_objectVsBroadPhaseFilter;
        m_impl->m_objectVsBroadPhaseFilter = nullptr;
        delete m_impl->m_objectLayerPairFilter;
        m_impl->m_objectLayerPairFilter = nullptr;

        // Delete job system and temp allocator
        delete m_impl->m_jobSystem;
        m_impl->m_jobSystem = nullptr;
        delete m_impl->m_tempAllocator;
        m_impl->m_tempAllocator = nullptr;
    }

    // Unregister and cleanup Jolt types
    JPH::UnregisterTypes();
    if (JPH::Factory::sInstance)
    {
        delete JPH::Factory::sInstance;
        JPH::Factory::sInstance = nullptr;
    }

    _currentPhysicsEngine = nullptr;
}

PhysicsEngine *PhysicsEngine::GetInstance()
{
    return _currentPhysicsEngine;
}

void PhysicsEngine::Initialize()
{
    LOG("Initializing Physics Engine...");

    // Register allocator and types
    JPH::RegisterDefaultAllocator();
    if (!JPH::VerifyJoltVersionID())
    {
        LOG("Jolt version mismatch between headers and libJolt.dylib");
        return;
    }
    if (JPH::Factory::sInstance == nullptr)
    {
        JPH::Factory::sInstance = new JPH::Factory();
    }
    JPH::RegisterTypes();

    // Create temporary allocator and job system used by Jolt
    m_impl->m_tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
    m_impl->m_jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::max(1u, std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() - 1 : 1u));

    // Initialize physics system with reasonable defaults
    const uint32_t maxBodies = 1024;
    const uint32_t numBodyMutexes = 0;
    const uint32_t maxBodyPairs = 1024;
    const uint32_t maxContactConstraints = 1024;

    // Provide simple layer/filter implementations similar to Jolt HelloWorld example
    // Layers: NON_MOVING = 0, MOVING = 1
    namespace LocalJolt = JPH;

    // Object layer pair filter
    class ObjectLayerPairFilterImpl final : public JPH::ObjectLayerPairFilter
    {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::ObjectLayer inLayer2) const override
        {
            // NON_MOVING (0) collides only with MOVING (1), MOVING collides with everything
            if (inLayer1 == 0) return inLayer2 == 1;
            return true;
        }
    };

    // Object vs broadphase filter
    class ObjectVsBroadPhaseLayerFilterImpl final : public JPH::ObjectVsBroadPhaseLayerFilter
    {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
        {
            if (inLayer1 == 0) return (JPH::BroadPhaseLayer::Type) inLayer2 == 1;
            return true;
        }
    };

    // BroadPhase layer interface table (simple mapping)
    class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
    {
    public:
        BPLayerInterfaceImpl()
        {
            mObjectToBroadPhase.resize(2, JPH::BroadPhaseLayer(0));
            mObjectToBroadPhase[0] = JPH::BroadPhaseLayer(0);
            mObjectToBroadPhase[1] = JPH::BroadPhaseLayer(1);
        }

        virtual uint GetNumBroadPhaseLayers() const override { return 2; }
        virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override { return mObjectToBroadPhase[inLayer]; }

    private:
        JPH::Array<JPH::BroadPhaseLayer> mObjectToBroadPhase;
    };

    m_impl->m_broadPhaseLayerInterface = new BPLayerInterfaceImpl();
    m_impl->m_objectVsBroadPhaseFilter = new ObjectVsBroadPhaseLayerFilterImpl();
    m_impl->m_objectLayerPairFilter = new ObjectLayerPairFilterImpl();

    m_impl->m_physicsSystem.Init(maxBodies, numBodyMutexes, maxBodyPairs, maxContactConstraints, *m_impl->m_broadPhaseLayerInterface, *m_impl->m_objectVsBroadPhaseFilter, *m_impl->m_objectLayerPairFilter);

    m_impl->m_bodyInterface = &m_impl->m_physicsSystem.GetBodyInterface();
}

void PhysicsEngine::Step(float deltaTime) const
{
    if (!m_impl->m_bodyInterface) return;

    // Determine collision steps (1 per 1/60s)
    int collisionSteps = std::max(1, (int) std::ceil(deltaTime * 60.0f));
    m_impl->m_physicsSystem.Update(deltaTime, collisionSteps, m_impl->m_tempAllocator, m_impl->m_jobSystem);
}

void *PhysicsEngine::CreateBoxBody(const glm::vec3 &halfExtents, const Location &worldLocation, BodyKind bodyKind, float mass, bool isCharacterBody) const
{
    if (!m_impl->m_bodyInterface) return nullptr;

    // Create shape (reference counted) so we don't leak shape allocations.
    JPH::BoxShapeSettings shapeSettings(JPH::Vec3(halfExtents.x, halfExtents.y, halfExtents.z));
    JPH::ShapeSettings::ShapeResult shapeResult = shapeSettings.Create();
    if (shapeResult.HasError())
    {
        LOG("Failed to create Jolt BoxShape: %s", shapeResult.GetError().c_str());
        return nullptr;
    }
    JPH::ShapeRefC shape = shapeResult.Get();

    // Convert location
    JPH::RVec3 jpos(worldLocation.GetX(), worldLocation.GetY(), worldLocation.GetZ());

    auto rot = JPH::Quat::sIdentity();

    JPH::EMotionType motion = JPH::EMotionType::Static;
    switch (bodyKind)
    {
        case BodyKind::Static:
            motion = JPH::EMotionType::Static;
            break;
        case BodyKind::Dynamic:
            motion = JPH::EMotionType::Dynamic;
            break;
        case BodyKind::Kinematic:
            motion = JPH::EMotionType::Kinematic;
            break;
    }

    JPH::ObjectLayer layer = bodyKind == BodyKind::Static ? JPH::ObjectLayer(0) : JPH::ObjectLayer(1);
    JPH::BodyCreationSettings settings(shape, jpos, rot, motion, layer);
    settings.mAllowSleeping = bodyKind != BodyKind::Kinematic;
    settings.mCollideKinematicVsNonDynamic = bodyKind == BodyKind::Kinematic;
    if (bodyKind == BodyKind::Kinematic)
    {
        settings.mMotionQuality = JPH::EMotionQuality::LinearCast;
    } else if (isCharacterBody)
    {
        settings.mAllowSleeping = false;
        settings.mMotionQuality = JPH::EMotionQuality::LinearCast;
        settings.mAllowedDOFs = JPH::EAllowedDOFs::TranslationX | JPH::EAllowedDOFs::TranslationY | JPH::EAllowedDOFs::TranslationZ;
    }

    // Create the body and add it to the world
    JPH::Body *body = m_impl->m_bodyInterface->CreateBody(settings);
    if (!body)
    {
        LOG("FAILED to create Jolt body.");
        return nullptr;
    }

    m_impl->m_bodyInterface->AddBody(body->GetID(), JPH::EActivation::Activate);

    LOG("Created BoxBody: %s at (%f, %f, %f)", isCharacterBody ? "Character" : (bodyKind == BodyKind::Static ? "Static" : "Dynamic"), worldLocation.GetX(), worldLocation.GetY(), worldLocation.GetZ());

    // Return a copy of BodyID as opaque handle
    return new JPH::BodyID(body->GetID());
}

Location PhysicsEngine::GetBodyLocation(void *bodyHandle) const
{
    if (!bodyHandle || !m_impl->m_bodyInterface) return Location();

    auto *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (!idPtr) return Location();

    JPH::RVec3 position = m_impl->m_bodyInterface->GetPosition(*idPtr);
    return Location(position.GetX(), position.GetY(), position.GetZ());
}

glm::vec3 PhysicsEngine::GetBodyLinearVelocity(void *bodyHandle) const
{
    if (!bodyHandle || !m_impl->m_bodyInterface) return glm::vec3(0.0f);

    auto *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (!idPtr) return glm::vec3(0.0f);

    JPH::Vec3 velocity = m_impl->m_bodyInterface->GetLinearVelocity(*idPtr);
    return glm::vec3(velocity.GetX(), velocity.GetY(), velocity.GetZ());
}

void PhysicsEngine::SetBodyLocation(void *bodyHandle, const Location &worldLocation)
{
    if (!bodyHandle || !m_impl->m_bodyInterface) return;

    auto *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (!idPtr) return;

    auto pos = worldLocation.AsVec3();
    m_impl->m_bodyInterface->SetPositionAndRotation(*idPtr, JPH::RVec3(pos.x, pos.y, pos.z), JPH::Quat::sIdentity(), JPH::EActivation::Activate);
}

void PhysicsEngine::SetBodyLinearVelocity(void *bodyHandle, const glm::vec3 &linearVelocity)
{
    if (!bodyHandle || !m_impl->m_bodyInterface) return;

    auto *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (!idPtr) return;

    m_impl->m_bodyInterface->SetLinearVelocity(*idPtr, JPH::Vec3(linearVelocity.x, linearVelocity.y, linearVelocity.z));
}

void PhysicsEngine::MoveKinematicBody(void *bodyHandle, const Location &targetLocation, float deltaTime)
{
    if (!bodyHandle || !m_impl->m_bodyInterface) return;

    auto *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (!idPtr) return;

    auto pos = targetLocation.AsVec3();
    m_impl->m_bodyInterface->MoveKinematic(*idPtr, JPH::RVec3(pos.x, pos.y, pos.z), JPH::Quat::sIdentity(), deltaTime);
}

void PhysicsEngine::DestroyBody(void *bodyHandle)
{
    if (!bodyHandle) return;
    // Interpret the opaque handle
    JPH::BodyID *idPtr = reinterpret_cast<JPH::BodyID *>(bodyHandle);
    if (m_impl->m_bodyInterface && idPtr)
    {
        // Convert back to BodyID and remove
        JPH::BodyID id = *idPtr;
        m_impl->m_bodyInterface->RemoveBody(id);
        m_impl->m_bodyInterface->DestroyBody(id);
    }
    delete idPtr;
}
