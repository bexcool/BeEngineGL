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

    [[nodiscard]] GameObject *GetParent() const;

    void Destroy();

    // World
    [[nodiscard]] Transform GetWorldTransform() const;
    [[nodiscard]] Location GetWorldLocation() const;
    [[nodiscard]] Rotation GetWorldRotation() const;
    [[nodiscard]] Scale GetWorldScale() const;

    // Local
    [[nodiscard]] Transform GetLocalTransform() const;
    void SetLocalTransform(Transform transform);
    [[nodiscard]] Location GetLocalLocation() const;
    void SetLocalLocation(Location location);
    [[nodiscard]] Rotation GetLocalRotation() const;
    void SetLocalRotation(Rotation rotation);
    [[nodiscard]] Scale GetLocalScale() const;
    void SetLocalScale(Scale scale);

    void OnTick() override {}
    void OnRender() override {}

    virtual void OnAttached(GameObject *parent);
    virtual void OnRemovedFromParent() {}
};
