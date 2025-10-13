//
// Created by Petr Pavlík on 29.09.2025.
//

#include "ModelComponent.h"

#include "../Graphics/ShaderProgram.h"
#include <iostream>

using namespace std;

void ModelComponent::LinkShaderProgram()
{
    _vertexShader = new Shader(GL_VERTEX_SHADER, _shaderInfo.GetVertexShaderPath());
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, _shaderInfo.GetFragmentShaderPath());
    _fragmentShader->Compile();

    _shaderProgram = new ShaderProgram(_vertexShader, _fragmentShader, this);
    _shaderProgram->LinkShaders();
}

ModelComponent::ModelComponent() {}

void ModelComponent::SetModel(const float *vertices, unsigned int amount)
{
    _amountOfVertices = amount;

    //vertex buffer object (VBO)
    _VBO = 0;
    glGenBuffers(1, &_VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _amountOfVertices * sizeof(float) * 6, vertices, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    _VAO = 0;
    glGenVertexArrays(1, &_VAO); //generate the VAO
    glBindVertexArray(_VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));

    LinkShaderProgram();
}

void ModelComponent::SetModel(const float *vertices, unsigned int amount, const ShaderInfo &shaderInfo)
{
    _shaderInfo = shaderInfo;

    SetModel(vertices, amount);
}

void ModelComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
}

void ModelComponent::OnRender()
{
    GameObjectComponent::OnRender();

    _shaderProgram->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
