//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include <glm/common.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"


class Transform
{
private:
    glm::mat4 _transformMatrix;
    Translation _translation;
    Rotation _rotation;
    Scale _scale;

public:
    Transform();

    Transform(Translation translation, Rotation rotation, Scale scale);

    Transform(glm::mat4 *transformMatrix);

    glm::mat4 *GetMatrix();
};
