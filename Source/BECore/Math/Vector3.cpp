//
// Created by Petr Pavlík on 15.10.2025.
//

#include "Vector3.h"

void Vector3::SetX(const float x)
{
    _x = x;
}

void Vector3::SetY(const float y)
{
    _y = y;
}

void Vector3::SetZ(const float z)
{
    _z = z;
}

Vector3 Vector3::operator+(const Vector3 &vector3) const
{
    return {_x + vector3._x, _y + vector3._y, _z + vector3._z};
}

Vector3 &Vector3::operator+=(const Vector3 &vector3)
{
    _x += vector3._x;
    _y += vector3._y;
    _z += vector3._z;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &vector3)
{
    _x -= vector3._x;
    _y -= vector3._y;
    _z -= vector3._z;
    return *this;
}

Vector3 Vector3::operator+=(const Vector3 &location) const
{
    return {_x + location.GetX(), _y + location.GetY(), _z + location.GetZ()};
}

Vector3 Vector3::operator*(const float &value) const
{
    return {value * this->GetX(), value * this->GetY(), value * this->GetZ()};
}
