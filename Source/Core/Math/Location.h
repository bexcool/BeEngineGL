//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include <glm/vec3.hpp>


class Location : public glm::vec3
{
public:
    Location() : glm::vec3(0.0f, 0.0f, 0.0f) {}
    Location(float x, float y, float z) : glm::vec3(x, y, z) {}

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }

    Location operator+(const Location &location) const;
};
