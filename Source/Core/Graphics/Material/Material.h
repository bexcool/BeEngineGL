//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once

#include <GL/glew.h>

#include "MaterialParameter.h"

#include "Core/Graphics/ShaderInfo.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include <unordered_map>
#include <string_view>

#define BE_MATERIAL(className, materialData) \
class className : public Material\
{\
    public:\
    className() : Material(#className, materialData) {}\
    virtual ~className() = default;\
};

struct MaterialData;
class ShaderProgram;

class Material
{
    std::string _materialName;

    std::shared_ptr<ShaderProgram> _shaderProgram = nullptr;

    void ApplyMaterialData(const MaterialData &materialData);

protected:
    struct MaterialCache
    {
        std::shared_ptr<ShaderProgram> shaderProgram;
    };

    ShaderInfo _shaderInfo = ShaderInfo();

    // Parameters
    MaterialParameter _diffuse;
    MaterialParameter _shininess;
    MaterialParameter _emission;

    static std::unordered_map<std::string, MaterialCache> MaterialInstances;

    void CreateShaderProgram();

public:
    Material();
    virtual ~Material() = default;

    // Copy constructor
    Material(const Material &other);

    // Initialization constructors
    Material(const std::string &materialName, const MaterialData &materialData);
    Material(const std::string &materialName, const MaterialData &materialData, const ShaderInfo &shaderInfo);
    Material(const std::string &materialName, const ShaderInfo &shaderInfo);

    MaterialParameter *GetParameter(MatParameterType type);

    ShaderInfo GetShaderInfo();
    std::shared_ptr<ShaderProgram> GetShaderProgram();

    [[nodiscard]] const std::string &GetMaterialName() const;
};

static const Material BE_DEFAULT_MATERIAL();
