//
// Created by Petr Pavlík on 08.11.2025.
//

#pragma once
#include "SkyBoxModel.h"
#include "../ShaderProgram.h"


class SkyBoxShaderProgram : public ShaderProgram
{
public:
    SkyBoxShaderProgram(Shader *vertexShader, Shader *fragmentShader, const ShaderInfo &shaderInfo, Transform *modelTransfrom) : ShaderProgram(vertexShader, fragmentShader, shaderInfo, modelTransfrom) {}

    void Use() override;
    void CreateTextures() override; // Co to je za blbost?
};
