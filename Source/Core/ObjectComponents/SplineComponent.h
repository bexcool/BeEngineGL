//
// Created by Petr Pavlík on 30.11.2025.
//

#pragma once
#include "GameObjectComponent.h"
#include "Core/Math/CurvePoint.h"


class SplineComponent : public GameObjectComponent
{
    glm::mat4x3 A;
    glm::mat4x3 B;

public:
    SplineComponent();
    SplineComponent(CurvePoint cp1, CurvePoint cp2);

    CurvePoint CurvePoint1;
    CurvePoint CurvePoint2;

    Location GetLocationFromAlpha(double alpha);
};
