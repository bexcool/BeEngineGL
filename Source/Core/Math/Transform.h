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
    Location _location;
    Rotation _rotation;
    Scale _scale;

public:
    Transform();

    Transform(Location translation, Rotation rotation, Scale scale);

    Transform(glm::mat4 *transformMatrix);

    glm::mat4 *AsMatrix();

    [[nodiscard]] Location GetLocation() const;
    void SetLocation(Location location);
    [[nodiscard]] Rotation GetRotation() const;
    void SetRotation(Rotation rotation);
    [[nodiscard]] Scale GetScale() const;
    void SetScale(Scale scale);
};
