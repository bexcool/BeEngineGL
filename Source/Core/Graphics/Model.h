//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "Shader.h"
#include "ShaderProgram.h"

#include <vector>

using namespace std;

class Model
{
private:
    Shader *_fragmentShader, *_vertexShader;
    ShaderProgram *_shaderProgram;
    vector<float> *_vertices;
    GLuint _VAO, _VBO;

public:
    Model(vector<float> *vertices);

    Model(Shader *fragmentShader, Shader *vertexShader, vector<float> *vertices);

    void Draw() const;
};
