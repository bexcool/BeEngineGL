//
// Created by Petr Pavlík on 30.11.2025.
//

#pragma once
#include "GameObjectComponent.h"


class SplineComponent : public GameObjectComponent
{
    glm::mat4 A;
    glm::mat4 B;

public:
    SplineComponent();

    Location GetLocationFromAlpha(double alpha);
};
