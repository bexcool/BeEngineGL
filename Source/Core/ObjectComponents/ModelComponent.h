//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderProgram.h"

#include <vector>

#include "GameObjectComponent.h"
#include "Core/Graphics/Model.h"
#include "Resources/Models/MOD_DefaultSphere.h"

using namespace std;

class ModelComponent : public GameObjectComponent
{
private:
    Model _model = MOD_DefaultSphere();

public:
    ModelComponent();

    void SetModel(Model model);

    void OnAttached(GameObject *parent) override;
    void OnRender() override;
    void OnTick() override;
};
