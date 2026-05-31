#include "ColliderComponent.h"

#include <algorithm>
#include <cmath>

#include "Core/Physics/PhysicsEngine.h"
#include "Core/logger.h"

std::vector<ColliderComponent *> ColliderComponent::Colliders = {};

ColliderComponent::ColliderComponent(const glm::vec3 &halfExtents, bool isTrigger, bool isStatic, float mass, bool isCharacterCollision)
    : GameObjectComponent("ColliderComponent"), _halfExtents(halfExtents), _isTrigger(isTrigger), _isStatic(isStatic), _isCharacterCollision(isCharacterCollision), _mass(mass) {}

ColliderComponent::~ColliderComponent()
{
    ColliderComponent::OnRemovedFromParent();
}

void ColliderComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
    Colliders.push_back(this);
}

void ColliderComponent::OnRemovedFromParent()
{
    auto physics = PhysicsEngine::GetInstance();
    if (physics && _bodyHandle)
    {
        physics->DestroyBody(_bodyHandle);
        _bodyHandle = nullptr;
    }

    Colliders.erase(std::remove(Colliders.begin(), Colliders.end(), this), Colliders.end());
    GameObjectComponent::OnRemovedFromParent();
}

void ColliderComponent::SyncPhysics()
{
    auto physics = PhysicsEngine::GetInstance();
    if (!physics) return;

    for (auto collider: Colliders)
    {
        if (!collider || !collider->GetParent()) continue;

        // Lazily create missing bodies (e.g. collider added before physics was initialized)
        if (!collider->_bodyHandle)
        {
            auto location = collider->GetParent()->GetWorldLocation();
            auto bodyKind = collider->_isCharacterCollision
                                ? PhysicsEngine::BodyKind::Dynamic
                                : (collider->_isStatic ? PhysicsEngine::BodyKind::Static : PhysicsEngine::BodyKind::Dynamic);
            collider->_bodyHandle = physics->CreateBoxBody(collider->_halfExtents, location, bodyKind, collider->_mass, collider->_isCharacterCollision);
            if (!collider->_bodyHandle) continue;
        }

        LOG("SYNC");

        if (collider->_isCharacterCollision || !collider->_isStatic)
        {
            // Sync game object from physics
            auto location = physics->GetBodyLocation(collider->_bodyHandle);
            collider->GetParent()->SetWorldLocation(location);
        } else
        {
            // Many game objects add components BEFORE calling SpawnGameObject(transform),
            // so the physics body may get created at the origin. Some physics backends also don't
            // support moving a truly static body after it has been added to the world.
            // We first try to move it; if it doesn't move, we recreate it at the correct location.
            const Location desiredLocation = collider->GetParent()->GetWorldLocation();
            const Location currentBodyLocation = physics->GetBodyLocation(collider->_bodyHandle);

            const glm::vec3 delta = desiredLocation.AsVec3() - currentBodyLocation.AsVec3();
            const float error = std::fabs(delta.x) + std::fabs(delta.y) + std::fabs(delta.z);

            if (error > 0.0005f)
            {
                physics->SetBodyLocation(collider->_bodyHandle, desiredLocation);

                const Location afterMoveLocation = physics->GetBodyLocation(collider->_bodyHandle);
                const glm::vec3 deltaAfter = desiredLocation.AsVec3() - afterMoveLocation.AsVec3();
                const float errorAfter = std::fabs(deltaAfter.x) + std::fabs(deltaAfter.y) + std::fabs(deltaAfter.z);

                if (errorAfter > 0.01f)
                {
                    // Recreate static body at correct position as a fallback.
                    physics->DestroyBody(collider->_bodyHandle);
                    collider->_bodyHandle = nullptr;

                    collider->_bodyHandle = physics->CreateBoxBody(
                        collider->_halfExtents,
                        desiredLocation,
                        PhysicsEngine::BodyKind::Static,
                        collider->_mass,
                        collider->_isCharacterCollision);
                }
            }
        }
    }
}
