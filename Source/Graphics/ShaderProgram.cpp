//
// Created by Petr Pavlík on 22.09.2025.
//

#include "ShaderProgram.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
}

void ShaderProgram::LinkShaders()
{
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _fragmentShader->GetShaderID());
    glAttachShader(_shaderProgram, _vertexShader->GetShaderID());
    glLinkProgram(_shaderProgram);

    _modelTransformId = glGetUniformLocation(_shaderProgram, "modelMatrix");

    _tmpMatrix = glm::mat4(1.0f); // construct identity matrix
    _tmpMatrix = glm::rotate<float>(glm::mat4(1.0f), (int) 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    GLint status;
    glGetProgramiv(GetShaderProgramID(), GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(GetShaderProgramID(), GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(GetShaderProgramID(), infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void ShaderProgram::Use()
{
    glUseProgram(GetShaderProgramID());
    glUniformMatrix4fv(_modelTransformId, 1, GL_FALSE, &_tmpMatrix[0][0]);
}
