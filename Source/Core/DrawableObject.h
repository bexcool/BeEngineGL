//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "Graphics/Model.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Transform.h"


class DrawableObject
{
private:
    Model *_model;
    ShaderProgram *_shaderProgram;
    Transform *_transform;

public:
    DrawableObject(Model *model, ShaderProgram *shaderProgram);

    DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transform);
};
