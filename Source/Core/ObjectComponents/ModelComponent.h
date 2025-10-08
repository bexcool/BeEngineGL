//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderProgram.h"

#include <vector>

#include "GameObjectComponent.h"

using namespace std;

class ModelComponent : public GameObjectComponent
{
private:
    Shader *_fragmentShader, *_vertexShader;
    ShaderProgram *_shaderProgram;
    unsigned int _amountOfVertices;
    GLuint _VAO = 0, _VBO = 0;

    void LinkShaderProgram();

public:
    ModelComponent() = default;

    void SetModel(const float *vertices, unsigned int amount);

    void OnAttached(GameObject *parent) override;
    void OnRender() override;
};
