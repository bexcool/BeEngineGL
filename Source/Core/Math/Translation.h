//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once


class Translation
{
private:
    float _x, _y, _z;

public:
    Translation() : _x(0), _y(0), _z(0) {}

    Translation(float x, float y, float z) : _x(x), _y(y), _z(z) {}

    float GetX() const { return _x; }
    float GetY() const { return _y; }
    float GetZ() const { return _z; }
};
