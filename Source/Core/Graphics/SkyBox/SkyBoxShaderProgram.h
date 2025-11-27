//
// Created by Petr Pavlík on 08.11.2025.
//

#pragma once
#include <utility>

#include "SkyBoxModel.h"
#include "../ShaderProgram.h"

class Material;

class SkyBoxShaderProgram : public ShaderProgram
{
public:
    CubeMap CubeMap;

    SkyBoxShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader, Material *material, std::shared_ptr<Transform> modelTransform) : ShaderProgram(vertexShader, fragmentShader, material, std::move(modelTransform)) {}

    void Use() override;
    void CreateTextures() override;
};
