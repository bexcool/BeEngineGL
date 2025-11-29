//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Scale.h"

glm::vec3 Scale::AsVec3() const
{
    return {_x, _y, _z};
}

Scale Scale::operator+(const Scale &scale) const
{
    return Scale(_x + scale._x, _y + scale._y, _z + scale._z);
}

Scale Scale::operator*(const Scale &scale) const
{
    return Scale(_x * scale._x, _y * scale._y, _z * scale._z);
}
