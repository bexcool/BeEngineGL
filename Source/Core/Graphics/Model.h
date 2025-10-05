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
    unsigned int _amountOfVertices;
    GLuint _VAO, _VBO;
    Transform *_transform; // error: unknown type name 'DrawableObject' - Nesnáším tohle!!!!!

public:
    Model(const float *vertices, const unsigned int amount, Transform *transform);

    //Model(Shader *fragmentShader, Shader *vertexShader, vector<float> *vertices);

    void Draw() const;
};
