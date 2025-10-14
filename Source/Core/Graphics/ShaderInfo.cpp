//
// Created by Petr Pavlík on 13.10.2025.
//

#include "ShaderInfo.h"

#include <utility>
#include <GL/glew.h>

ShaderInfo::ShaderInfo(std::string fragmentShaderPath)
{
    _fragmentShaderPath = std::move(fragmentShaderPath);
}

ShaderInfo::ShaderInfo(std::string shaderPath, int shaderType)
{
    switch (shaderType)
    {
        case GL_VERTEX_SHADER: _vertexShaderPath = std::move(shaderPath);
            break;
        case GL_FRAGMENT_SHADER: _fragmentShaderPath = std::move(shaderPath);
            break;
        default:
            _vertexShaderPath = std::move(shaderPath);
    }
}

ShaderInfo::ShaderInfo(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    _vertexShaderPath = std::move(vertexShaderPath);
    _fragmentShaderPath = std::move(fragmentShaderPath);
}

std::string ShaderInfo::GetVertexShaderPath()
{
    return _vertexShaderPath;
}

std::string ShaderInfo::GetFragmentShaderPath()
{
    return _fragmentShaderPath;
}
