//
// Created by Petr Pavlík on 31.05.2026.
//

#include "CapsuleCollisionComponent.h"

#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

CapsuleCollisionComponent::CapsuleCollisionComponent(float halfHeight,
                                                     float radius,
                                                     CollisionMotionType motionType,
                                                     bool isTrigger,
                                                     float mass)
    : CollisionComponent("CapsuleCollisionComponent", motionType, isTrigger, mass), _halfHeight(halfHeight), _radius(radius) {}

JPH::ShapeRefC CapsuleCollisionComponent::CreateShape()
{
    JPH::CapsuleShapeSettings settings(_halfHeight, _radius);
    return settings.Create().Get();
}
