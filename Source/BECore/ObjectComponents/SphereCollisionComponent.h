//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once

#include "CollisionComponent.h"

class SphereCollisionComponent : public CollisionComponent
{
    float _radius;

public:
    explicit SphereCollisionComponent(float radius,
                                      CollisionMotionType motionType = CollisionMotionType::Static,
                                      bool isTrigger = false,
                                      float mass = 1.0f);

    JPH::ShapeRefC CreateShape() override;
};
