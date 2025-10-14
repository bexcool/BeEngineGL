//
// Created by Petr Pavlík on 14.10.2025.
//

#include "Model.h"

void Model::LinkShaderProgram()
{
    _vertexShader = new Shader(GL_VERTEX_SHADER, _shaderInfo.GetVertexShaderPath());
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, _shaderInfo.GetFragmentShaderPath());
    _fragmentShader->Compile();

    _shaderProgram = new ShaderProgram(_vertexShader, _fragmentShader, &_transform);
    _shaderProgram->LinkShaders();
}

void Model::SetModel(const float *vertices, unsigned int amount)
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

void Model::SetModel(const float *vertices, unsigned int amount, const ShaderInfo &shaderInfo)
{
    _shaderInfo = shaderInfo;

    SetModel(vertices, amount);
}

void Model::Render(Transform transform)
{
    _transform = transform;

    _shaderProgram->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
