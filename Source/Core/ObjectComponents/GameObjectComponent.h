//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../Objects/GameObject.h"
#include "../Math/Transform.h"
#include "../Events/CoreEvents.h"
#include "../Events/KeyEvents.h"

class GameObject;

class GameObjectComponent : public CoreEvents, KeyEvents
{
    Transform _localTransform = Transform();
    GameObject *_parent;

public:
    GameObjectComponent() = default;

    GameObject *GetParent() const;

    // World
    Transform GetWorldTransform() const;
    void SetWorldTransform(const Transform transform);
    Location GetWorldLocation() const;
    void SetWorldLocation(const Location location);
    Rotation GetWorldRotation() const;
    void SetWorldRotation(const Rotation rotation);
    Scale GetWorldScale() const;
    void SetWorldScale(const Scale scale);

    // Local
    Transform GetLocalTransform() const;
    void SetLocalTransform(const Transform transform);
    Location GetLocalLocation() const;
    void SetLocalLocation(const Location location);
    Rotation GetLocalRotation() const;
    void SetLocalRotation(const Rotation rotation);
    Scale GetLocalScale() const;
    void SetLocalScale(const Scale scale);

    virtual void OnAttached(GameObject *parent);
    virtual void OnRemovedFromParent() {}
};
