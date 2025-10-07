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
