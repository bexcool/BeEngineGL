//
// Created by Petr Pavlík on 08.10.2025.
//

#include "GameObjectComponent.h"

GameObject *GameObjectComponent::GetParent() const
{
    return _parent;
}

Transform GameObjectComponent::GetWorldTransform() const
{
    return _parent->GetWorldTransform() + _localTransform;
}

void GameObjectComponent::SetWorldTransform(const Transform transform)
{
    _localTransform = transform;
}

void GameObjectComponent::SetWorldLocation(const Location location)
{
    _localTransform.SetLocation(location);
}

void GameObjectComponent::SetWorldRotation(const Rotation rotation)
{
    _localTransform.SetRotation(rotation);
}

void GameObjectComponent::SetWorldScale(const Scale scale)
{
    _localTransform.SetScale(scale);
}

Transform GameObjectComponent::GetLocalTransform() const
{
    return _localTransform;
}

void GameObjectComponent::SetLocalTransform(const Transform transform)
{
    _localTransform = transform;
}

Location GameObjectComponent::GetLocalLocation() const
{
    return _localTransform.GetLocation();
}

void GameObjectComponent::SetLocalLocation(const Location location)
{
    _localTransform.SetLocation(location);
}

Rotation GameObjectComponent::GetLocalRotation() const
{
    return _localTransform.GetRotation();
}

void GameObjectComponent::SetLocalRotation(const Rotation rotation)
{
    _localTransform.SetRotation(rotation);
}

Scale GameObjectComponent::GetLocalScale() const
{
    return _localTransform.GetScale();
}

void GameObjectComponent::SetLocalScale(const Scale scale)
{
    _localTransform.SetScale(scale);
}

Location GameObjectComponent::GetWorldLocation() const
{
    return GetWorldTransform().GetLocation();
}

Rotation GameObjectComponent::GetWorldRotation() const
{
    return GetWorldTransform().GetRotation();
}

Scale GameObjectComponent::GetWorldScale() const
{
    return GetWorldTransform().GetScale();
}

void GameObjectComponent::OnAttached(GameObject *parent)
{
    _parent = parent;
}
