//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once

#include "Vector3.h"

class Location : public Vector3
{
public:
    Location() : Vector3() {};
    explicit Location(const Vector3 &v) : Vector3(v) {}
    Location(float x, float y, float z) : Vector3(x, y, z) {}
};
