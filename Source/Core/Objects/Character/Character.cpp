//
// Created by Petr Pavlík on 08.10.2025.
//

#include "Character.h"

void Character::SetWalkSpeed(const float speed)
{
    _walkSpeed = speed;
}

float Character::GetWalkSpeed() const
{
    return _walkSpeed;
}

void Character::SetRunSpeed(const float speed)
{
    _runSpeed = speed;
}

float Character::GetRunSpeed() const
{
    return _runSpeed;
}
