//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>

class Shader
{
private:
    GLuint _shaderID;
    int _shaderType;
    std::string _shaderSource;

public:
    Shader(int shaderType, std::string shaderSource) : _shaderType(shaderType), _shaderSource(shaderSource) {}

    void Compile();

    GLuint GetShaderID() { return _shaderID; }
};
