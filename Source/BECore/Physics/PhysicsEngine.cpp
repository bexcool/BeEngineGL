//
// Created by Petr Pavlík on 31.05.2026.
//

#include "PhysicsEngine.h"

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>

#include "BECore/ObjectComponents/CollisionComponent.h"
#include "BECore/ObjectComponents/CharacterCollisionComponent.h"

#include "BECore/logger.h"

#include <thread>

#include "BECore/Application.h"

class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
    JPH::uint GetNumBroadPhaseLayers() const override
    {
        return BPLayers::NUM_LAYERS;
    }

    JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
    {
        switch (inLayer)
        {
            case PhysicsLayers::NON_MOVING: return BPLayers::NON_MOVING;
            case PhysicsLayers::MOVING: return BPLayers::MOVING;
            default: return BPLayers::NON_MOVING;
        }
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    const char *GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override
    {
        switch ((JPH::BroadPhaseLayer::Type) inLayer)
        {
            case 0: return "NON_MOVING";
            case 1: return "MOVING";
            default: return "INVALID";
        }
    }
#endif
};

class ObjectVsBroadPhaseLayerFilterImpl final : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    bool ShouldCollide(JPH::ObjectLayer inLayer, JPH::BroadPhaseLayer inBPLayer) const override
    {
        switch (inLayer)
        {
            case PhysicsLayers::NON_MOVING: return inBPLayer == BPLayers::MOVING;
            case PhysicsLayers::MOVING: return true;
            default: return false;
        }
    }
};

class ObjectLayerPairFilterImpl final : public JPH::ObjectLayerPairFilter
{
public:
    bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::ObjectLayer inLayer2) const override
    {
        switch (inLayer1)
        {
            case PhysicsLayers::NON_MOVING: return inLayer2 == PhysicsLayers::MOVING;
            case PhysicsLayers::MOVING: return true;
            default: return false;
        }
    }
};

PhysicsEngine *PhysicsEngine::_instance = nullptr;

PhysicsEngine::PhysicsEngine()
{
    _instance = this;
}

PhysicsEngine::~PhysicsEngine()
{
    delete _physicsSystem;
    _physicsSystem = nullptr;
    delete _jobSystem;
    _jobSystem = nullptr;
    delete _tempAllocator;
    _tempAllocator = nullptr;

    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;

    _instance = nullptr;
}

void PhysicsEngine::Initialize()
{
    LOG("Initializing physics engine...");

    LOG("[Jolt] Registering default allocator...");
    JPH::RegisterDefaultAllocator();

    LOG("[Jolt] Creating factory...");
    JPH::Factory::sInstance = new JPH::Factory();

    LOG("[Jolt] Registering types...");
    JPH::RegisterTypes();

    LOG("[Jolt] Creating temp allocator...");
    _tempAllocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);

    LOG("[Jolt] Initializing job system...");
    int numThreads = std::max(1, (int) std::thread::hardware_concurrency() - 1);
    _jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, numThreads);

    static BPLayerInterfaceImpl bpLayerInterface;
    static ObjectVsBroadPhaseLayerFilterImpl ovbpFilter;
    static ObjectLayerPairFilterImpl olpFilter;

    _physicsSystem = new JPH::PhysicsSystem();

    LOG("[Jolt] Initializing...");
    _physicsSystem->Init(2048, 0, 65536, 10240, bpLayerInterface, ovbpFilter, olpFilter);

    LOG("[Jolt] Settings gravity...");
    _physicsSystem->SetGravity(JPH::Vec3(0.0f, -9.81f, 0.0f));

    LOG("Physics system initialized.");
}

void PhysicsEngine::Step(float deltaTime)
{
    if (!_physicsSystem) return;

    CollisionComponent::CreatePending();
    CharacterCollisionComponent::CreatePending();

    CharacterCollisionComponent::UpdateAll(deltaTime);

    _physicsSystem->Update(deltaTime, 1, _tempAllocator, _jobSystem);

    CollisionComponent::SyncDynamic();
}

JPH::BodyInterface &PhysicsEngine::GetBodyInterface()
{
    return _physicsSystem->GetBodyInterface();
}

HitResult PhysicsEngine::TraceLine(Location start, Vector3 direction, float distance)
{
    const JPH::NarrowPhaseQuery &query = PhysicsEngine::GetInstance()
            ->GetPhysicsSystem()->GetNarrowPhaseQueryNoLock();

    JPH::RRayCast ray{
        JPH::Vec3(start.GetX(), start.GetY(), start.GetZ()),
        JPH::Vec3(direction.GetX(), direction.GetY(), direction.GetZ()) * distance
    };

    JPH::RayCastResult result;
    HitResult hitResult;

    bool traceHit = query.CastRay(ray, result);
    hitResult.blockingHit = traceHit;

    if (traceHit)
    {
        JPH::BodyID hitBody = result.mBodyID;
        hitResult.bodyID = hitBody;
        hitResult.fraction = result.mFraction;

        JPH::Vec3 hitPosition = ray.GetPointOnRay(result.mFraction);

        // If hit is too far away, return
        if (glm::distance(start.AsVec3(), glm::vec3(hitPosition.GetX(), hitPosition.GetY(), hitPosition.GetZ())) > distance)
        {
            hitResult.blockingHit = false;
            return hitResult;
        }

        hitResult.location = Location(hitPosition.GetX(), hitPosition.GetY(), hitPosition.GetZ());

        auto gos = *Application::GetInstance()->GetLevel()->GetGameObjects();
        for (auto currentGO: gos)
        {
            auto components = currentGO->GetComponents();
            for (auto currentGOC: components)
            {
                if (auto *collisionComponent = dynamic_cast<CollisionComponent *>(currentGOC))
                {
                    if (collisionComponent->GetBodyID() == hitBody)
                    {
                        hitResult.hitObject = currentGO;
                        hitResult.hitComponent = currentGOC;

                        return hitResult;
                    }
                }
            }
        }
    }

    return hitResult;
}
