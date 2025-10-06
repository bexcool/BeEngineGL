//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "Shader.h"
#include "ShaderProgram.h"

#include <vector>

class DrawableObject;
using namespace std;

class Model
{
private:
    Shader *_fragmentShader, *_vertexShader;
    ShaderProgram *_shaderProgram;
    unsigned int _amountOfVertices;
    GLuint _VAO, _VBO;
    DrawableObject *_parent; // error: unknown type name 'DrawableObject' - Nesnáším tohle!!!!!

public:
    Model(const float *vertices, const unsigned int amount);

    //Model(Shader *fragmentShader, Shader *vertexShader, vector<float> *vertices);

    void Initialize(DrawableObject *parent);

    void SetParent(DrawableObject *parent);

    void Draw() const;
};
