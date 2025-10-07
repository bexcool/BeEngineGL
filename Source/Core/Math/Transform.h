//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include <glm/common.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "Rotation.h"
#include "Scale.h"
#include "Location.h"


class Transform
{
private:
    glm::mat4 _transformMatrix;
    Location _translation;
    Rotation _rotation;
    Scale _scale;

public:
    Transform();

    Transform(Location translation, Rotation rotation, Scale scale);

    Transform(glm::mat4 *transformMatrix);

    glm::mat4 *AsMatrix();

    Location GetLocation();
    Rotation GetRotation();
    Scale GetScale();
};
