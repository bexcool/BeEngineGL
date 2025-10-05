//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once


class Rotation
{
private:
    float _x, _y, _z;

public:
    Rotation() : _x(0.0f), _y(0.0f), _z(0.0f) {}

    Rotation(float roll, float pitch, float yaw) : _x(roll), _y(pitch), _z(yaw) {}

    float GetRoll() const { return _x; }
    float GetPitch() const { return _y; }
    float GetYaw() const { return _z; }
};
