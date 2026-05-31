//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../GameObject.h"


class Character : public GameObject
{
    double _walkSpeed = 1.0;
    double _runSpeed = 6.0;

public:
    void SetWalkSpeed(float speed);
    [[nodiscard]] float GetWalkSpeed() const;
    void SetRunSpeed(float speed);
    [[nodiscard]] float GetRunSpeed() const;
};
