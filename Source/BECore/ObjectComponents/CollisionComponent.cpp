//
// Created by Petr Pavlík on 31.05.2026.
//

#include "CollisionComponent.h"

#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BECore/Physics/PhysicsEngine.h"
#include "BECore/Objects/GameObject.h"
#include "BECore/Math/Rotation.h"

#include <Jolt/Physics/Body/BodyCreationSettings.h>

std::vector<CollisionComponent *> CollisionComponent::AllCollisionComponents;

CollisionComponent::CollisionComponent(std::string name, CollisionMotionType motionType, bool isTrigger, float mass)
    : GameObjectComponent(std::move(name)), _motionType(motionType), _isTrigger(isTrigger), _mass(mass) {}

CollisionComponent::~CollisionComponent()
{
    // Remove from list and destroy body if not already done by OnRemovedFromParent.
    auto it = std::find(AllCollisionComponents.begin(), AllCollisionComponents.end(), this);
    if (it != AllCollisionComponents.end()) AllCollisionComponents.erase(it);

    auto *pe = PhysicsEngine::GetInstance();
    if (pe && !_bodyID.IsInvalid())
    {
        pe->GetBodyInterface().RemoveBody(_bodyID);
        pe->GetBodyInterface().DestroyBody(_bodyID);
        _bodyID = JPH::BodyID();
    }
}

void CollisionComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
    AllCollisionComponents.push_back(this);
    // Body is created in CreatePending() during the first physics step, after the parent
    // has been given its world position by SpawnGameObject.
}

void CollisionComponent::CreatePending()
{
    auto *pe = PhysicsEngine::GetInstance();
    if (!pe) return;

    for (auto *comp: AllCollisionComponents)
    {
        if (!comp->_bodyID.IsInvalid()) continue;
        
        auto *parent = comp->GetParent();
        if (!parent) continue;

        JPH::ShapeRefC shape = comp->CreateShape();

        auto loc = comp->GetWorldLocation();
        glm::quat glmQuat = comp->GetWorldRotation().AsQuat();

        JPH::RVec3 pos((float) loc.GetX(), (float) loc.GetY(), (float) loc.GetZ());
        JPH::Quat jphRot(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);

        JPH::EMotionType motionType;
        JPH::ObjectLayer layer;
        switch (comp->_motionType)
        {
            case CollisionMotionType::Kinematic:
                motionType = JPH::EMotionType::Kinematic;
                layer = PhysicsLayers::MOVING;
                break;
            case CollisionMotionType::Dynamic:
                motionType = JPH::EMotionType::Dynamic;
                layer = PhysicsLayers::MOVING;
                break;
            default:
                motionType = JPH::EMotionType::Static;
                layer = PhysicsLayers::NON_MOVING;
                break;
        }

        JPH::BodyCreationSettings settings(shape, pos, jphRot, motionType, layer);
        if (comp->_motionType == CollisionMotionType::Dynamic)
        {
            settings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
            settings.mMassPropertiesOverride.mMass = comp->_mass;
        }

        comp->_bodyID = pe->GetBodyInterface().CreateAndAddBody(settings, JPH::EActivation::Activate);
    }
}

void CollisionComponent::OnRemovedFromParent()
{
    auto it = std::find(AllCollisionComponents.begin(), AllCollisionComponents.end(), this);
    if (it != AllCollisionComponents.end()) AllCollisionComponents.erase(it);

    auto *pe = PhysicsEngine::GetInstance();
    if (!pe || _bodyID.IsInvalid()) return;

    pe->GetBodyInterface().RemoveBody(_bodyID);
    pe->GetBodyInterface().DestroyBody(_bodyID);
    _bodyID = JPH::BodyID();
}

void CollisionComponent::OnTick()
{
    GameObjectComponent::OnTick();
}

void CollisionComponent::SyncKinematic(float deltaTime)
{
    auto *pe = PhysicsEngine::GetInstance();
    if (!pe) return;

    for (auto *comp: AllCollisionComponents)
    {
        if (comp->_motionType != CollisionMotionType::Kinematic || comp->_bodyID.IsInvalid()) continue;

        auto *parent = comp->GetParent();
        if (!parent) continue;

        auto loc = parent->GetWorldLocation();
        glm::quat glmQuat = parent->GetWorldRotation().AsQuat();

        JPH::RVec3 pos((float) loc.GetX(), (float) loc.GetY(), (float) loc.GetZ());
        JPH::Quat jphRot(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);

        pe->GetBodyInterface().MoveKinematic(comp->_bodyID, pos, jphRot, deltaTime);
    }
}

void CollisionComponent::SyncDynamic()
{
    auto *pe = PhysicsEngine::GetInstance();
    if (!pe) return;

    for (auto *comp: AllCollisionComponents)
    {
        if (comp->_motionType != CollisionMotionType::Dynamic || comp->_bodyID.IsInvalid()) continue;

        auto *parent = comp->GetParent();
        if (!parent) continue;

        JPH::RVec3 pos = pe->GetBodyInterface().GetPosition(comp->_bodyID);
        JPH::Quat rot = pe->GetBodyInterface().GetRotation(comp->_bodyID);

        // Convert Jolt quaternion to engine Rotation (XZY Euler convention: Roll=X, Pitch=Z, Yaw=Y).
        glm::quat glmQuat(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ());
        glm::mat4 rotMat = glm::mat4_cast(glmQuat);
        float roll, pitch, yaw;
        glm::extractEulerAngleXZY(rotMat, roll, pitch, yaw);

        parent->SetWorldLocation(Location((float) pos.GetX(), (float) pos.GetY(), (float) pos.GetZ()));
        parent->SetWorldRotation(Rotation(glm::degrees(roll), glm::degrees(pitch), glm::degrees(yaw)));
    }
}
