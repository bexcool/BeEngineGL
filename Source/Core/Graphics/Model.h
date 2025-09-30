//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "Shader.h"
#include "ShaderProgram.h"


class Model
{
private:
    Shader *_fragmentShader, *_vertexShader;
    ShaderProgram *_shaderProgram;
    float *vertices;

public:
    Model(float vertices[]);

    Model(Shader *fragmentShader, Shader *vertexShader, float *vertices);
};
