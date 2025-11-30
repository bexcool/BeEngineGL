//
// Created by Petr Pavlík on 24.11.2025.
//

#pragma once
#include "Core/Level.h"
#include "Core/ObjectComponents/SplineComponent.h"


class SolarSystemLevel : public Level
{
    GameObject *goEarth = nullptr, *goUFO = nullptr;
    SplineComponent *spline = nullptr;

public:
    SolarSystemLevel() : Level("SolarSystemLevel") {};
    virtual ~SolarSystemLevel() = default;
    void OnLoaded() override;
    void OnTick() override;
};

