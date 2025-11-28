//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include <glm/ext/quaternion_float.hpp>

class Rotation
{
private:
    float _x, _y, _z;

public:
    Rotation() : _x(0.0f), _y(0.0f), _z(0.0f) {}

    Rotation(float pitch, float yaw, float roll) : _x(pitch), _y(yaw), _z(roll) {}

    [[nodiscard]] float GetPitch() const { return _x; }
    [[nodiscard]] float GetYaw() const { return _y; }
    [[nodiscard]] float GetRoll() const { return _z; }
    [[nodiscard]] glm::vec3 GetForwardVector() const;

    [[nodiscard]] glm::quat AsQuat() const;

    Rotation operator+(const Rotation &rotation) const;
};
