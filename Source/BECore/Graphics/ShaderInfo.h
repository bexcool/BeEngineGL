//
// Created by Petr Pavlík on 13.10.2025.
//

#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <utility>


struct ShaderInfo
{
    std::string vertexShaderPath = "./Resources/Shaders/default.vert";
    std::string fragmentShaderPath = "./Resources/Shaders/phong.frag";
    bool useTexture = false;
    std::string texturePath = "./Resources/Assets/Textures/DefaultTexture.png";
    glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
};
