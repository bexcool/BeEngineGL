//
// Created by Petr Pavlík on 22.09.2025.
//

#include "ShaderProgram.h"

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
}
