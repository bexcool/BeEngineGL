//
// Created by Petr Pavlík on 08.10.2025.
//

#include "GameObjectComponent.h"

GameObjectComponent::~GameObjectComponent()
{
    GameObjectComponent::OnRemovedFromParent();
}

GameObject *GameObjectComponent::GetParent() const
{
    return _parent;
}

void GameObjectComponent::Destroy()
{
    delete this;
}

Transform GameObjectComponent::GetWorldTransform() const
{
    //return _parent->GetWorldTransform() + _localTransform;

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(_parent->GetWorldRotation().GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(_parent->GetWorldRotation().GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(_parent->GetWorldRotation().GetRoll()), glm::vec3(0.0f, 0.0f, 1.0f));

    auto actualLocation = glm::vec3(rotation * glm::vec4(GetLocalLocation().AsVec3() - _parent->GetWorldLocation().AsVec3(), 1.0f)) + _parent->GetWorldLocation().AsVec3();

    return Transform(Location(Location(actualLocation) + _parent->GetWorldLocation()), GetLocalRotation() + _parent->GetWorldRotation(), GetLocalScale() + _parent->GetWorldTransform().GetScale());
}

Transform GameObjectComponent::GetLocalTransform() const
{
    return _localTransform;
}

void GameObjectComponent::SetLocalTransform(const Transform &transform)
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
