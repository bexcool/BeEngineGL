//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "Scale.h"
#include "Location.h"
#include "Rotation.h"

class Transform
{
    glm::mat4 _transformMatrix = glm::mat4(1.0f);
    Location _location = Location();
    Rotation _rotation = Rotation();
    Scale _scale = Scale();

    void RecreateTransformMatrix();

public:
    Transform() = default;
    Transform(Location translation, Rotation rotation, Scale scale);
    Transform(glm::mat4 *transformMatrix);

    glm::mat4 AsMatrix();

    [[nodiscard]] Location GetLocation() const;
    void SetLocation(Location location);
    [[nodiscard]] Rotation GetRotation() const;
    void SetRotation(Rotation rotation);
    [[nodiscard]] Scale GetScale() const;
    void SetScale(Scale scale);

    Transform operator+(const Transform &transform) const;
};
