//
// Created by Petr Pavlík on 31.05.2026.
//

#include "SphereCollisionComponent.h"

#include <Jolt/Physics/Collision/Shape/SphereShape.h>

SphereCollisionComponent::SphereCollisionComponent(float radius,
                                                   CollisionMotionType motionType,
                                                   bool isTrigger,
                                                   float mass)
    : CollisionComponent("SphereCollisionComponent", motionType, isTrigger, mass), _radius(radius) {}

JPH::ShapeRefC SphereCollisionComponent::CreateShape()
{
    JPH::SphereShapeSettings settings(_radius);
    return settings.Create().Get();
}
