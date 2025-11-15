//
// Created by Petr Pavlík on 06.11.2025.
//

#include "./SkyBoxModel.h"

#include "SkyBoxShaderProgram.h"
#include "Core/Application.h"
#include "Libs/stb_image.h"
#include "Resources/Assets/Models/MOD_SkyBox.h"

SkyBoxModel::SkyBoxModel()
{
    SetModelCustomSP("./Resources/Assets/Models/cube.obj", ShaderInfo{.fragmentShaderPath = "./Resources/Shaders/skybox.frag.glsl", .vertexShaderPath = "./Resources/Shaders/skybox.vert.glsl", .useTexture = true});

    LinkShaderProgram();
}

void SkyBoxModel::LinkShaderProgram()
{
    _vertexShader = new Shader(GL_VERTEX_SHADER, _shaderInfo.vertexShaderPath);
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, _shaderInfo.fragmentShaderPath);
    _fragmentShader->Compile();

    _shaderProgram = new SkyBoxShaderProgram(_vertexShader, _fragmentShader, _shaderInfo, _transform.get());
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
