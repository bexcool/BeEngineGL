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
    std::string _displayName;

    Transform _localTransform = Transform();
    GameObject *_parent = nullptr;

    bool _lockRoll = false;
    bool _lockPitch = false;
    bool _lockYaw = false;

public:
    explicit GameObjectComponent(std::string name);
    ~GameObjectComponent() override;

    [[nodiscard]] GameObject *GetParent() const;

    void Destroy();

    // Rotation
    void SetRotationLock(bool lockRoll, bool lockPitch, bool lockYaw);

    // World
    [[nodiscard]] Transform GetWorldTransform() const;
    [[nodiscard]] Location GetWorldLocation() const;
    [[nodiscard]] Rotation GetWorldRotation() const;
    [[nodiscard]] Scale GetWorldScale() const;

    // Local
    [[nodiscard]] Transform GetLocalTransform() const;
    void SetLocalTransform(const Transform &transform);
    [[nodiscard]] Location GetLocalLocation() const;
    void SetLocalLocation(Location location);
    [[nodiscard]] Rotation GetLocalRotation() const;
    void SetLocalRotation(Rotation rotation);
    [[nodiscard]] Scale GetLocalScale() const;
    void SetLocalScale(Scale scale);

    // Engine events
    void OnTick() override {}
    void OnRender() override {}

    virtual void OnAttached(GameObject *parent);
    virtual void OnRemovedFromParent() {}
};
