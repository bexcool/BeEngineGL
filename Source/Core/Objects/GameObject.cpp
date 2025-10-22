//
// Created by Petr Pavlík on 07.10.2025.
//

#include "GameObject.h"

#include "Core/Application.h"

void GameObject::OnTick()
{
    for (auto comp: GetComponents())
    {
        comp->OnTick();
    }

    _controller->OnTick();
}

void GameObject::OnRender()
{
    for (auto comp: GetComponents())
    {
        comp->OnRender();
    }
}

GameObject::~GameObject()
{
    _controller.reset();

    for (auto comp: GetComponents())
    {
        comp->Destroy();
    }
}

void GameObject::Destroy()
{
    _destroyRequested = true;
}

bool GameObject::GetDestroyRequested() const
{
    return _destroyRequested;
}

void GameObject::SetName(const std::string &name)
{
    _name = name;
}

std::string GameObject::GetName()
{
    return _name;
}

bool GameObject::IsSpawned()
{
    return _spawned;
}

void GameObject::SetController(std::unique_ptr<Controller> controller)
{
    _controller = std::move(controller);
    _controller->OnPossessed(this);
}

Controller *GameObject::GetController() const
{
    return _controller.get();
}

void GameObject::AddComponent(GameObjectComponent *component)
{
    _components.push_back(component);

    if (auto lc = dynamic_cast<LightComponent *>(component))
    {
        Application::GetInstance()->GetLevel()->AddLightComponent(lc);
    }

    component->OnAttached(this);
}

void GameObject::AddComponent(GameObjectComponent *component, const Transform transform)
{
    component->SetLocalTransform(transform);
    AddComponent(component);
}

void GameObject::RemoveComponent(GameObjectComponent *component)
{
    _components.erase(std::find(_components.begin(), _components.end(), component));
    component->OnRemovedFromParent();
}

std::vector<GameObjectComponent *> &GameObject::GetComponents()
{
    return _components;
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

void GameObject::AddWorldLocation(const Location &worldLocation)
{
    _worldTransform.SetLocation(Location(worldLocation + GetWorldLocation()));
}

Rotation GameObject::GetWorldRotation() const
{
    return _worldTransform.GetRotation();
}

void GameObject::SetWorldRotation(const Rotation &worldRotation)
{
    _worldTransform.SetRotation(worldRotation);
}

void GameObject::OnSpawned()
{
    _spawned = true;
}
