//
// Created by Petr Pavlík on 06.11.2025.
//

#include <utility>

#include "./SkyBoxModel.h"

#include "SkyBoxShaderProgram.h"
#include "Core/Application.h"
#include "Libs/stb_image.h"
#include "Resources/Assets/Models/MOD_SkyBox.h"

SkyBoxModel::SkyBoxModel(CubeMap cubeMap)
{
    this->_cubeMap = std::move(cubeMap);

    SetModelCustomSP("./Resources/Assets/Models/cube.obj", ShaderInfo{.fragmentShaderPath = "./Resources/Shaders/skybox.frag.glsl", .vertexShaderPath = "./Resources/Shaders/skybox.vert.glsl", .useTexture = true});

    LinkShaderProgram();
}

void SkyBoxModel::LinkShaderProgram()
{
    const auto si = _material->get()->GetShaderInfo();
    _vertexShader = new Shader(GL_VERTEX_SHADER, si.vertexShaderPath);
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, si.fragmentShaderPath);
    _fragmentShader->Compile();

    _shaderProgram = new SkyBoxShaderProgram(_vertexShader, _fragmentShader, si, _transform.get());
    dynamic_cast<SkyBoxShaderProgram *>(_shaderProgram)->CubeMap = _cubeMap;
    _shaderProgram->LinkShaders();
    dynamic_cast<SkyBoxShaderProgram *>(_shaderProgram)->CreateTextures();
}

void SkyBoxModel::Render()
{
    auto cam = Application::GetInstance()->GetLevel()->GetActiveCamera();

    *_transform = cam->GetWorldLocation();

    dynamic_cast<SkyBoxShaderProgram *>(_shaderProgram)->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
