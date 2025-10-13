//
// Created by Petr Pavlík on 13.10.2025.
//

#pragma once
#include <string>


class ShaderInfo
{
    std::string _vertexShaderPath = "./Resources/Shaders/default.vert";
    std::string _fragmentShaderPath = "./Resources/Shaders/default.frag";

public:
    ShaderInfo() = default;
    ShaderInfo(std::string shaderPath, int shaderType);
    ShaderInfo(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~ShaderInfo() = default;

    std::string GetVertexShaderPath();
    std::string GetFragmentShaderPath();
};
