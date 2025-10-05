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
    this->_transform = new Transform();
}

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader, Transform *transform)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
    this->_transform = transform;
}

void ShaderProgram::LinkShaders()
{
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _fragmentShader->GetShaderID());
    glAttachShader(_shaderProgram, _vertexShader->GetShaderID());
    glLinkProgram(_shaderProgram);

    _modelTransformId = glGetUniformLocation(_shaderProgram, "modelMatrix");

    GLint status;
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(_shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void ShaderProgram::Use()
{
    glUseProgram(_shaderProgram);
    glUniformMatrix4fv(_modelTransformId, 1, GL_FALSE, &(*_transform->GetMatrix())[0][0]);
}
