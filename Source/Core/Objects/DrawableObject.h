//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "GameObject.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Math/Transform.h"

class DrawableObject : public GameObject
{
private:
    Model *_model;

public:
    DrawableObject() = default;

    void SetModel(Model *model);

    void OnRender() override;
};
