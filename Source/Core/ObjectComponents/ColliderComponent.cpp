//
// Simple AABB collider implementation
//
#include "ColliderComponent.h"

#include <algorithm>

#include "Core/logger.h"

std::vector<ColliderComponent *> ColliderComponent::Colliders = {};

ColliderComponent::ColliderComponent(const glm::vec3 &halfExtents, bool isTrigger, bool isStatic, float mass)
    : GameObjectComponent("ColliderComponent"), _halfExtents(halfExtents), _isTrigger(isTrigger), _isStatic(isStatic), _mass(mass) {}

ColliderComponent::~ColliderComponent()
{
    OnRemovedFromParent();
}

void ColliderComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
    Colliders.push_back(this);
}

void ColliderComponent::OnRemovedFromParent()
{
    Colliders.erase(std::remove(Colliders.begin(), Colliders.end(), this), Colliders.end());
    GameObjectComponent::OnRemovedFromParent();
}

void ColliderComponent::ResolveCollision(ColliderComponent *mover, Location &desiredLocation)
{
    if (!mover) return;

    glm::vec3 moverHalf = mover->GetHalfExtents();

    glm::vec3 moverCenter = desiredLocation.AsVec3();

    for (auto other: Colliders)
    {
        if (other == mover) continue;
        if (other->IsTrigger()) continue;
        if (!other->GetParent()) continue;

        glm::vec3 otherCenter = other->GetParent()->GetWorldLocation().AsVec3();
        glm::vec3 otherHalf = other->GetHalfExtents();

        // compute overlap on each axis
        glm::vec3 delta = moverCenter - otherCenter;
        glm::vec3 overlap = glm::vec3(moverHalf.x + otherHalf.x - std::abs(delta.x),
                                      moverHalf.y + otherHalf.y - std::abs(delta.y),
                                      moverHalf.z + otherHalf.z - std::abs(delta.z));

        if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0)
        {
            // collision detected; compute minimal translation vector (mtv)
            glm::vec3 mtv(0.0f);
            if (overlap.x <= overlap.y && overlap.x <= overlap.z)
            {
                mtv.x = (delta.x >= 0) ? overlap.x : -overlap.x;
            } else if (overlap.y <= overlap.x && overlap.y <= overlap.z)
            {
                mtv.y = (delta.y >= 0) ? overlap.y : -overlap.y;
            } else
            {
                mtv.z = (delta.z >= 0) ? overlap.z : -overlap.z;
            }

            // resolve depending on static/movable
            if (other->_isStatic && mover->_isStatic)
            {
                // both static: nothing to do
            } else if (other->_isStatic && !mover->_isStatic)
            {
                // push mover fully out
                moverCenter += mtv;
            } else if (!other->_isStatic && mover->_isStatic)
            {
                // push other fully out
                auto otherParent = other->GetParent();
                if (otherParent)
                {
                    otherParent->SetWorldLocation(Location(otherCenter - mtv));
                }
            } else
            {
                // both movable: split resolution equally (could use mass)
                float moverShare = 0.5f;
                float otherShare = 1.0f - moverShare;

                moverCenter += mtv * moverShare;
                auto otherParent = other->GetParent();
                if (otherParent)
                {
                    otherParent->SetWorldLocation(Location(otherCenter - mtv * otherShare));
                }
            }
        }
    }

    // write back
    desiredLocation = Location(moverCenter);
}
