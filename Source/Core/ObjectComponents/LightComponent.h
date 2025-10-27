//
// Created by Petr Pavlík on 14.10.2025.
//

#pragma once
#include "GameObjectComponent.h"
#include "Core/Graphics/Light.h"


class LightComponent : public GameObjectComponent
{
    Light _light = Light();

public:
    LightComponent() = default;
    explicit LightComponent(const Light &light);

    Light GetLight();
    void SetLight(Light light);

    float GetWorldIntensity();
};
