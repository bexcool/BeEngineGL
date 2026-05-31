//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once

#include <vector>

#include "GameObjectComponent.h"
#include "BECore/Graphics/Model.h"
#include "Resources/Assets/Models/MOD_Sphere.h"

using namespace std;

class ModelComponent : public GameObjectComponent
{
    Model _model = MOD_Sphere();

public:
    ModelComponent() : GameObjectComponent("ModelComponent") {};
    explicit ModelComponent(const Model &model);
    explicit ModelComponent(const Transform &relativeTransform);
    ModelComponent(const Model &model, const Transform &relativeTransform);

    void SetModel(const Model &model);
    Model GetModel();

    void OnAttached(GameObject *parent) override;
    void OnRender() override;
    void OnTick() override;
};
