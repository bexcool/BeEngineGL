//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include "MaterialParameter.h"
#include "Core/Graphics/ShaderInfo.h"
#include "Resources/Assets/Textures/TEX_Default.h"

#define BE_MATERIAL(className) \
    class className : public Material

class ShaderProgram;

class Material
{
    std::shared_ptr<ShaderProgram> _shaderProgram = nullptr;

protected:
    ShaderInfo _shaderInfo = ShaderInfo();
    MaterialParameter _diffuse = MaterialParameter(TEX_Default());

    void LinkShaderProgram();

public:
    Material();
    ~Material() = default;
    explicit Material(const ShaderInfo &shaderInfo);

    MaterialParameter *GetParameter(MatParameterType type);

    ShaderInfo GetShaderInfo();
    std::shared_ptr<ShaderProgram> GetShaderProgram();
};

static const Material BE_DEFAULT_MATERIAL();
