//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include <glm/ext/quaternion_float.hpp>

class Rotation
{
    float _x, _y, _z;

public:
    Rotation() : _x(0.0f), _y(0.0f), _z(0.0f) {}

    Rotation(float roll, float pitch, float yaw) : _x(roll), _y(pitch), _z(yaw) {}

    [[nodiscard]] float GetRoll() const { return _x; }
    [[nodiscard]] float GetPitch() const { return _y; }
    [[nodiscard]] float GetYaw() const { return _z; }
    [[nodiscard]] glm::vec3 GetForwardVector() const;

    [[nodiscard]] glm::quat AsQuat() const;

    Rotation operator+(const Rotation &rotation) const;
    Rotation operator-(const Rotation &rotation) const;
};
