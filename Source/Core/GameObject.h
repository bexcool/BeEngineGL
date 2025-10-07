//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include "Math/Transform.h"


class GameObject
{
    Transform _worldTransform;

public:
    Transform GetWorldTransform() const;
    void SetWorldTransform(const Transform &worldTransform);

    Location GetWorldLocation() const;
    void SetWorldLocation(const Location &worldLocation);

    Rotation GetWorldRotation() const;
    void SetWorldRotation(const Rotation &worldRotation);
};
