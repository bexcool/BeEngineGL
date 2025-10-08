//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include <vector>

#include "../ObjectComponents/GameObjectComponent.h"
#include "../Math/Transform.h"
#include "../Controllers/Controller.h"
#include "../Events/KeyboardKeyEventArgs.h"

class GameObjectComponent;
class Controller;

class GameObject : public ICoreEvents
{
    Transform _worldTransform = Transform();
    std::vector<GameObjectComponent *> _components;

protected:
    std::unique_ptr<Controller> _controller = std::make_unique<Controller>();

public:
    GameObject() = default;
    ~GameObject() override;

    void Destroy();

    // Controller
    void SetController(std::unique_ptr<Controller> controller);
    Controller *GetController() const;

    // Components
    void AddComponent(GameObjectComponent *component);
    void AddComponent(GameObjectComponent *component, const Transform transform);
    void RemoveComponent(GameObjectComponent *component);
    std::vector<GameObjectComponent *> &GetComponents();

    // Transform
    Transform GetWorldTransform() const;
    void SetWorldTransform(const Transform &worldTransform);

    Location GetWorldLocation() const;
    void SetWorldLocation(const Location &worldLocation);

    Rotation GetWorldRotation() const;
    void SetWorldRotation(const Rotation &worldRotation);

    // Virtual
    virtual void OnSpawned() {}

    // Overrides
    void OnRender() override;
    void OnTick() override;
};
