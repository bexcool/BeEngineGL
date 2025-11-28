//
// Created by Petr Pavlík on 29.09.2025.
//

#include "ModelComponent.h"

#include <utility>

#include "Core/logger.h"

ModelComponent::ModelComponent(const Model &model)
{
    SetModel(model);
}

ModelComponent::ModelComponent(const Transform &relativeTransform)
{
    SetLocalTransform(relativeTransform);
}

ModelComponent::ModelComponent(const Model &model, const Transform &relativeTransform)
{
    SetLocalTransform(relativeTransform);
    SetModel(model);
}

void ModelComponent::SetModel(const Model &model)
{
    _model = model;
}

Model ModelComponent::GetModel()
{
    return _model;
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
