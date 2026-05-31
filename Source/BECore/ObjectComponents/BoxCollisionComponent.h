//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once

#include "CollisionComponent.h"
#include <glm/vec3.hpp>

class BoxCollisionComponent : public CollisionComponent
{
    glm::vec3 _halfExtents;

public:
    explicit BoxCollisionComponent(glm::vec3 halfExtents = {1, 1, 1},
                                   CollisionMotionType motionType = CollisionMotionType::Static,
                                   bool isTrigger = false,
                                   float mass = 1.0f);

    JPH::ShapeRefC CreateShape() override;
};
