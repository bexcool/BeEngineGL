//
// Created by Petr Pavlík on 31.05.2026.
//

#include "BoxCollisionComponent.h"

#include <Jolt/Physics/Collision/Shape/BoxShape.h>

BoxCollisionComponent::BoxCollisionComponent(glm::vec3 halfExtents,
                                             CollisionMotionType motionType,
                                             bool isTrigger,
                                             float mass)
    : CollisionComponent("BoxCollisionComponent", motionType, isTrigger, mass), _halfExtents(halfExtents) {}

JPH::ShapeRefC BoxCollisionComponent::CreateShape()
{
    JPH::BoxShapeSettings settings(JPH::Vec3(_halfExtents.x, _halfExtents.y, _halfExtents.z));
    return settings.Create().Get();
}
