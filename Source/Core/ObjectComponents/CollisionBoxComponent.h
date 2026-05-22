//
// Created by Petr Pavlík on 22.05.2026.
//

#pragma once

#include "ColliderComponent.h"

class CollisionBoxComponent : public ColliderComponent
{
public:
    CollisionBoxComponent() : ColliderComponent(glm::vec3(1)) {}
};
