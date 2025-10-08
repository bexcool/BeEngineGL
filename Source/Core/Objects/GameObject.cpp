//
// Created by Petr Pavlík on 07.10.2025.
//

#include "GameObject.h"

void GameObject::Controller_KeyboardKeyPressed(KeyboardKeyEventArgs e)
{
    for (auto comp: _components)
    {
        //comp->On
    }
}

void GameObject::SetController(std::unique_ptr<Controller> controller)
{
    _controller = std::move(controller);
    _controller.get()->OnPossessed(this);
}

Controller *GameObject::GetController() const
{
    return _controller.get();
}

void GameObject::AddComponent(GameObjectComponent *component)
{
    _components.push_back(component);
    component->OnAttached(this);
}

void GameObject::RemoveComponent(GameObjectComponent *component)
{
    _components.erase(std::find(_components.begin(), _components.end(), component));
    component->OnRemovedFromParent();
}

std::vector<GameObjectComponent *> *GameObject::GetComponents()
{
    return &_components;
}

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
