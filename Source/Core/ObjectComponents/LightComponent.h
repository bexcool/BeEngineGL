//
// Created by Petr Pavlík on 14.10.2025.
//

#pragma once
#include "GameObjectComponent.h"
#include "Core/Graphics/Light.h"


class LightComponent : public GameObjectComponent
{
    Light _light = {.intensity = 1};

public:
    LightComponent() = default;

    Light GetLight();
    void SetLight(Light light);

    float GetWorldIntensity();
};
