//
// Created by Petr Pavlík on 29.09.2025.
//

#include "ModelComponent.h"

#include <utility>

#include "Core/logger.h"

ModelComponent::ModelComponent(Model _model)
{
    SetModel(_model);
}

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

    _model.Render(GetWorldTransform());
}

void ModelComponent::OnTick()
{
    GameObjectComponent::OnTick();
}
