//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include <glm/common.hpp>
#include <glm/ext/matrix_float4x4.hpp>


class Transform
{
private:
    glm::mat4 *transformMatrix;

public:
    Transform();

    Transform(glm::mat4 *transformMatrix);
};
