//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include "MaterialParameter.h"
#include "Core/Graphics/ShaderInfo.h"
#include "Resources/Assets/Textures/TEX_Default.h"

#define BE_MATERIAL(className, materialData) \
class className : public Material\
{\
    public:\
    className() : Material(materialData) {}\
};

struct MaterialData;
class ShaderProgram;

class Material
{
    std::shared_ptr<ShaderProgram> _shaderProgram = nullptr;

    void ApplyMaterialData(const MaterialData &materialData);

protected:
    ShaderInfo _shaderInfo = ShaderInfo();
    MaterialParameter _diffuse = MaterialParameter(TEX_Default());

    void CreateShaderProgram();

public:
    Material();
    ~Material() = default;

    // Copy constructor
    Material(const Material &other);

    // Initialization constructors
    explicit Material(const MaterialData &materialData);
    Material(const MaterialData &materialData, const ShaderInfo &shaderInfo);
    explicit Material(const ShaderInfo &shaderInfo);

    MaterialParameter *GetParameter(MatParameterType type);

    ShaderInfo GetShaderInfo();
    std::shared_ptr<ShaderProgram> GetShaderProgram();
};

static const Material BE_DEFAULT_MATERIAL();
