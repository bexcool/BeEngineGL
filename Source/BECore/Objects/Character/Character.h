//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../GameObject.h"

class CharacterCollisionComponent;

class Character : public GameObject
{
    double _walkSpeed = 3.0;
    double _runSpeed = 9.0;

protected:
    CharacterCollisionComponent *_characterCollision = nullptr;

public:
    void SetWalkSpeed(float speed);
    [[nodiscard]] float GetWalkSpeed() const;
    void SetRunSpeed(float speed);
    [[nodiscard]] float GetRunSpeed() const;

    [[nodiscard]] CharacterCollisionComponent *GetCharacterCollision() const { return _characterCollision; }
};
