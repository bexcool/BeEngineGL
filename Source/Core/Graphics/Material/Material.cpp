//
// Created by Petr Pavlík on 25.11.2025.
//

#include "./Material.h"

#include "Core/Graphics/Shader.h"
#include "Core/Graphics/ShaderProgram.h"

void Material::LinkShaderProgram()
{
    const auto si = this->GetShaderInfo();
    auto _vertexShader = std::make_shared<Shader>(GL_VERTEX_SHADER, si.vertexShaderPath);
    _vertexShader->Compile();

    auto _fragmentShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER, si.fragmentShaderPath);
    _fragmentShader->Compile();

    _shaderProgram = std::make_shared<ShaderProgram>(_vertexShader, _fragmentShader, this);
    _shaderProgram->LinkShaders();
    _shaderProgram->CreateTextures();
}

Material::Material()
{
    LinkShaderProgram();
}

Material::Material(const ShaderInfo &shaderInfo)
{
    _shaderInfo = shaderInfo;

    LinkShaderProgram();
}

MaterialParameter *Material::GetParameter(MatParameterType type)
{
    switch (type)
    {
        case MatParameterType::Diffuse: return &_diffuse;
    }
    return nullptr;
}

ShaderInfo Material::GetShaderInfo()
{
    return _shaderInfo;
}

std::shared_ptr<ShaderProgram> Material::GetShaderProgram()
{
    return _shaderProgram;
}

