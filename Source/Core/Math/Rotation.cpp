//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Rotation.h"

Rotation Rotation::operator+(const Rotation &rotation) const
{
    return {GetRoll() + rotation.GetRoll(), GetPitch() + rotation.GetPitch(), GetYaw() + rotation.GetYaw()};
}
