//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include <glm/vec3.hpp>

class Scale
{
private:
    float _x, _y, _z;

public:
    Scale() : _x(1), _y(1), _z(1) {}

    explicit Scale(float scale) : _x(scale), _y(scale), _z(scale) {}

    Scale(float x, float y, float z) : _x(x), _y(y), _z(z) {}
    explicit Scale(glm::vec3 scale) : _x(scale.x), _y(scale.y), _z(scale.z) {}

    [[nodiscard]] float GetX() const { return _x; }
    [[nodiscard]] float GetY() const { return _y; }
    [[nodiscard]] float GetZ() const { return _z; }

    [[nodiscard]] glm::vec3 AsVec3() const;

    Scale operator+(const Scale &scale) const;
    Scale operator*(const Scale &scale) const;
};
