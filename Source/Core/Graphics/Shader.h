//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <sstream>
#include <glm/vec4.hpp>

class Shader
{
    GLuint _shaderID;
    int _shaderType;
    std::string _shaderPath;

public:
    Shader(int shaderType, std::string shaderPath) : _shaderType(shaderType), _shaderPath(shaderPath) {}

    static std::string ShaderTypeToString(int shaderType);

    void Compile();
    GLuint GetShaderID() { return _shaderID; }
};
