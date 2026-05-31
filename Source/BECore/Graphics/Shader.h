//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <utility>

class Shader
{
    GLuint _shaderID;
    int _shaderType;
    std::string _shaderPath;

public:
    Shader(int shaderType, std::string shaderPath) : _shaderType(shaderType), _shaderPath(std::move(shaderPath)) {}

    static std::string ShaderTypeToString(int shaderType);

    void Compile();
    [[nodiscard]] GLuint GetShaderID() const { return _shaderID; }
};
