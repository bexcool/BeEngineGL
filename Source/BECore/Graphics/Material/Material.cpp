//
// Created by Petr Pavlík on 25.11.2025.
//

#include "./Material.h"

#include <typeinfo>

#include "Core/Graphics/Shader.h"
#include "Core/Graphics/ShaderProgram.h"
#include "Core/logger.h"
#include "MaterialData.h"

std::unordered_map<std::string, Material::MaterialCache> Material::MaterialInstances;

void Material::ApplyMaterialData(const MaterialData& materialData) {
    _diffuse = materialData.diffuse;
    _shininess = materialData.shininess;
    _emission = materialData.emission;
}

void Material::CreateShaderProgram() {
    // Do not create new model, if the old one exists
    auto foundMaterial = MaterialInstances.find(GetMaterialName());
    if (foundMaterial != MaterialInstances.end()) {
        const auto& existingMaterial = foundMaterial->second;

        _shaderProgram = existingMaterial.shaderProgram;
        _shaderProgram->SetMaterial(this);

        LOG("Material already exists. Referencing data... Path: %s S. P. Id: %d", GetMaterialName().c_str(), _shaderProgram->GetShaderProgramId());

        return;
    }

    if (_shaderProgram != nullptr) {
        LOG_W("Material: CreateShaderProgram: Attempted to create a new ShaderProgram when it already exists!");
    }

    const auto si = this->GetShaderInfo();
    auto _vertexShader = std::make_shared<Shader>(GL_VERTEX_SHADER, si.vertexShaderPath);
    _vertexShader->Compile();

    auto _fragmentShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER, si.fragmentShaderPath);
    _fragmentShader->Compile();

    _shaderProgram = std::make_shared<ShaderProgram>(_vertexShader, _fragmentShader, this);
    _shaderProgram->LinkShaders();
    _shaderProgram->CreateTextures();

    MaterialCache newCache;

    newCache.shaderProgram = _shaderProgram;

    MaterialInstances[GetMaterialName()] = newCache;
}

Material::Material() {
    _materialName = "Material";

    CreateShaderProgram();
}

Material::Material(const Material& other) : _shaderInfo(other._shaderInfo),
                                            _diffuse(other._diffuse),
                                            _shininess(other._shininess),
                                            _emission(other._emission),
                                            _materialName(other._materialName) {
    _shaderProgram = nullptr;

    CreateShaderProgram();
}

Material::Material(const std::string& materialName, const MaterialData& materialData) {
    _materialName = materialName;

    ApplyMaterialData(materialData);
    CreateShaderProgram();
}

Material::Material(const std::string& materialName, const MaterialData& materialData, const ShaderInfo& shaderInfo) {
    _materialName = materialName;
    _shaderInfo = shaderInfo;

    ApplyMaterialData(materialData);
    CreateShaderProgram();
}

Material::Material(const std::string& materialName, const ShaderInfo& shaderInfo) {
    _materialName = materialName;
    _shaderInfo = shaderInfo;

    CreateShaderProgram();
}

const MaterialParameter* Material::GetParameter(MatParameterType type) const {
    switch (type) {
        case MatParameterType::Diffuse:
            return &_diffuse;
        case MatParameterType::Shininess:
            return &_shininess;
        case MatParameterType::Emission:
            return &_emission;
    }
    return nullptr;
}

ShaderInfo Material::GetShaderInfo() {
    return _shaderInfo;
}

std::shared_ptr<ShaderProgram> Material::GetShaderProgram() {
    return _shaderProgram;
}

const std::string& Material::GetMaterialName() const {
    return _materialName;
}
