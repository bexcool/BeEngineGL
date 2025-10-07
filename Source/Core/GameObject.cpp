//
// Created by Petr Pavlík on 07.10.2025.
//

#include "GameObject.h"

Transform GameObject::GetWorldTransform() const
{
    return _worldTransform;
}

void GameObject::SetWorldTransform(const Transform &worldTransform)
{
    _worldTransform = worldTransform;
}

Location GameObject::GetWorldLocation() const
{
    return _worldTransform.GetLocation();
}


void GameObject::SetWorldLocation(const Location &worldLocation)
{
    _worldTransform.SetLocation(worldLocation);
}

Rotation GameObject::GetWorldRotation() const
{
    return _worldTransform.GetRotation();
}

void GameObject::SetWorldRotation(const Rotation &worldRotation)
{
    _worldTransform.SetRotation(worldRotation);
}
