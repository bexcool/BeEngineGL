//
// Created by Petr Pavlík on 08.11.2025.
//

#pragma once
#include <utility>

#include "../ShaderProgram.h"
#include "SkyBoxModel.h"

class Material;

class SkyBoxShaderProgram : public ShaderProgram {
   public:
    CubeMap CubeMap;
    std::shared_ptr<Transform> _modelTransform;

    SkyBoxShaderProgram(const std::shared_ptr<Shader>& vertexShader, const std::shared_ptr<Shader>& fragmentShader, Material* material, std::shared_ptr<Transform> modelTransform) : ShaderProgram(vertexShader, fragmentShader, material), _modelTransform(std::move(modelTransform)) {}

    void Use() override;
    void CreateTextures() override;
};
