//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Scale.h"

Scale Scale::operator+(const Scale &scale) const
{
    return Scale(_x + scale._x, _y + scale._y, _z + scale._z);
}
