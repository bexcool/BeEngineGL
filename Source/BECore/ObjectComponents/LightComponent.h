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
    LightComponent() : GameObjectComponent("ModelComponent") {};
    explicit LightComponent(const Light &light);

    [[nodiscard]] Light GetLight() const;
    void SetLight(Light light);

    float GetWorldIntensity();
};
