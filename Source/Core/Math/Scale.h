//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once

class Scale
{
private:
    float _x, _y, _z;

public:
    Scale() : _x(1), _y(1), _z(1) {}

    Scale(float scale) : _x(scale), _y(scale), _z(scale) {}

    Scale(float x, float y, float z) : _x(x), _y(y), _z(z) {}

    float GetX() const { return _x; }
    float GetY() const { return _y; }
    float GetZ() const { return _z; }

    Scale operator+(const Scale &scale) const;
};
