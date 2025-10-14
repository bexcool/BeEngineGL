//
// Created by Petr Pavlík on 29.09.2025.
//

#include "ModelComponent.h"

#include <utility>

ModelComponent::ModelComponent() {}

void ModelComponent::SetModel(Model model)
{
    _model = std::move(model);
}

void ModelComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
}

void ModelComponent::OnRender()
{
    GameObjectComponent::OnRender();
}

void ModelComponent::OnTick()
{
    GameObjectComponent::OnTick();

    _model.Render(GetWorldTransform());
}
