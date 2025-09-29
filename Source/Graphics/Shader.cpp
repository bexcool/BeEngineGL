//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Shader.h"

void Shader::Compile()
{
    _shaderID = glCreateShader(_shaderType);
    const char *src = _shaderSource.c_str();
    glShaderSource(_shaderID, 1, &src, NULL);
    glCompileShader(_shaderID);

    GLint status;
    glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(_shaderID, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "%s Shader compilation failed: %s\n", _shaderType, strInfoLog);
        delete[] strInfoLog;
    }
}
