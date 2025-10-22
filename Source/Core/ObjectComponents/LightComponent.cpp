//
// Created by Petr Pavlík on 14.10.2025.
//

#include "LightComponent.h"

Light LightComponent::GetLight()
{
    return _light;
}

void LightComponent::SetLight(Light light)
{
    _light = light;
}

float LightComponent::GetWorldIntensity()
{
    if (!GetParent()->IsSpawned())
    {
        return 0.0f;
    }

    return _light.intensity;
}
