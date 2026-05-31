//
// Created by Petr Pavlík on 06.11.2025.
//

#include <utility>

#include "./SkyBoxModel.h"

#include "SkyBoxShaderProgram.h"
#include "BECore/Application.h"
#include "Libs/stb_image.h"
#include "Resources/Assets/Models/MOD_SkyBox.h"

SkyBoxModel::SkyBoxModel(CubeMap cubeMap)
{
    this->_cubeMap = std::move(cubeMap);

    SetModelCustomSP("./Resources/Assets/Models/cube.obj", Material("SkyBox", ShaderInfo{.vertexShaderPath = "./Resources/Shaders/skybox.vert.glsl", .fragmentShaderPath = "./Resources/Shaders/skybox.frag.glsl", .useTexture = true}));

    LinkShaderProgram();
}

void SkyBoxModel::LinkShaderProgram()
{
    const auto si = _material->GetShaderInfo();
    _vertexShader = std::make_shared<Shader>(GL_VERTEX_SHADER, si.vertexShaderPath);
    _vertexShader->Compile();

    _fragmentShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER, si.fragmentShaderPath);
    _fragmentShader->Compile();

    auto tmpSp = std::make_shared<SkyBoxShaderProgram>(_vertexShader, _fragmentShader, _material.get(), _transform);
    tmpSp->CubeMap = _cubeMap;
    tmpSp->LinkShaders();
    tmpSp->CreateTextures();

    _shaderProgram = tmpSp;
}

void SkyBoxModel::Render()
{
    auto cam = Application::GetInstance()->GetLevel()->GetActiveCamera();

    *_transform = cam->GetWorldLocation();

    _shaderProgram->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
