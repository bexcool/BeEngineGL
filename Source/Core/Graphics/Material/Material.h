//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include "MaterialParameter.h"
#include "Core/Graphics/ShaderProgram.h"


class Material
{
    ShaderProgram *_shaderProgram = nullptr;

protected:
    ShaderInfo _shaderInfo = ShaderInfo();
    MaterialParameter _diffuse = MaterialParameter();

public:
    ShaderInfo GetShaderInfo();
};
