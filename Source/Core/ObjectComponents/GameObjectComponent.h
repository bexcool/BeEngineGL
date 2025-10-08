//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../Objects/GameObject.h"
#include "../Math/Transform.h"
#include "Core/Interfaces/ICoreEvents.h"

class GameObject;

class GameObjectComponent : public ICoreEvents
{
    Transform _localTransform = Transform();
    GameObject *_parent = nullptr;

public:
    GameObjectComponent() = default;
    ~GameObjectComponent() override;

    GameObject *GetParent() const;

    void Destroy();

    // World
    Transform GetWorldTransform() const;
    Location GetWorldLocation() const;
    Rotation GetWorldRotation() const;
    Scale GetWorldScale() const;

    // Local
    Transform GetLocalTransform() const;
    void SetLocalTransform(Transform transform);
    Location GetLocalLocation() const;
    void SetLocalLocation(Location location);
    Rotation GetLocalRotation() const;
    void SetLocalRotation(Rotation rotation);
    Scale GetLocalScale() const;
    void SetLocalScale(Scale scale);

    void OnTick() override {}
    void OnRender() override {}

    virtual void OnAttached(GameObject *parent);
    virtual void OnRemovedFromParent() {}
};
