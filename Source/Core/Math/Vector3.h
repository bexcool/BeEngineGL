//
// Created by Petr Pavlík on 15.10.2025.
//

#pragma once
#include <glm/vec3.hpp>

class Vector3
{
    float _x = 0;
    float _y = 0;
    float _z = 0;

public:
    Vector3() = default;
    Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
    explicit Vector3(glm::vec<3, float> vec) : _x(vec.x), _y(vec.y), _z(vec.z) {}

    [[nodiscard]] float GetX() const { return _x; }
    [[nodiscard]] float GetY() const { return _y; }
    [[nodiscard]] float GetZ() const { return _z; }

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    [[nodiscard]] glm::vec3 AsVec3() const { return {_x, _y, _z}; }

    Vector3 operator+(const Vector3 &vector3) const;
    Vector3 &operator+=(const Vector3 &vector3);
    Vector3 &operator-=(const Vector3 &vector3);
    Vector3 operator+=(const Vector3 &vector3) const;

    Vector3 operator*(const float &value) const;
};

inline Vector3 operator*(float value, const Vector3 &vec)
{
    return vec * value;
}
