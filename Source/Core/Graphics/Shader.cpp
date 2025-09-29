//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Shader.h"
#include <iostream>
#include <fstream>

using namespace std;

std::string Shader::ShaderTypeToString(int shaderType)
{
    switch (shaderType)
    {
        case GL_VERTEX_SHADER:
            return "Vertex Shader";
        case GL_FRAGMENT_SHADER:
            return "Fragment Shader";
    }
}

void Shader::Compile()
{
    _shaderID = glCreateShader(_shaderType);
    string shader;

    fstream file("filename.txt");

    std::ostringstream ss;
    ss << file.rdbuf(); // read entire buffer into stream
    std::string shaderCode = ss.str();
    const char *src = shaderCode.c_str();

    file.close();

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
        fprintf(stderr, "%s Shader compilation failed: %s\n",
                ShaderTypeToString(_shaderType).c_str(),
                strInfoLog);
        delete[] strInfoLog;
    }
}
