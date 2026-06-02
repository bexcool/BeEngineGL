//
// Created by Petr Pavlík on 08.10.2025.
//

#include "GameObjectComponent.h"

#include <utility>

GameObjectComponent::GameObjectComponent(std::string name)
{
    _displayName = std::move(name);
}

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

void GameObjectComponent::SetRotationLock(bool lockRoll, bool lockPitch, bool lockYaw)
{
    _lockRoll = lockRoll;
    _lockPitch = lockPitch;
    _lockYaw = lockYaw;
}

Transform GameObjectComponent::GetWorldTransform() const
{
    if (!_parent) return GetLocalTransform();

    const auto &parentTransform = _parent->GetWorldTransform();
    Rotation parentRot = parentTransform.GetRotation();
    Scale parentScale = parentTransform.GetScale();

    glm::mat4 rotation(1.0f);
    // Keep the same axis convention as Transform::RecreateTransformMatrix()
    rotation = glm::rotate(rotation, glm::radians(parentRot.GetRoll()), glm::vec3(1, 0, 0)); // roll around X
    rotation = glm::rotate(rotation, glm::radians(parentRot.GetPitch()), glm::vec3(0, 0, 1)); // pitch around Z
    rotation = glm::rotate(rotation, glm::radians(parentRot.GetYaw()), glm::vec3(0, 1, 0)); // yaw around Y

    glm::vec3 scaledLocalPos = GetLocalLocation().AsVec3() * parentScale.AsVec3();
    glm::vec3 worldPos = parentTransform.GetLocation().AsVec3() + glm::vec3(rotation * glm::vec4(scaledLocalPos, 1.0f));

    Rotation actualRot{_lockRoll ? 0 : parentRot.GetRoll(), _lockPitch ? 0 : parentRot.GetPitch(), _lockYaw ? 0 : parentRot.GetYaw()};

    return {Location(worldPos), actualRot + GetLocalRotation(), parentScale * GetLocalScale()};
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

Vector3 GameObjectComponent::GetForwardVector() const
{
    return Vector3(glm::normalize(GetWorldRotation().AsQuat() * glm::vec3(1.0f, 0.0f, 0.0f)));
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
