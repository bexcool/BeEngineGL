//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "../Math/Transform.h"

class Model;

class ShaderProgram
{
private:
	GLuint _shaderProgram;
	Shader *_vertexShader;
	Shader *_fragmentShader;
	GLuint _modelTransformId;
	GLuint _projectionTransformId;
	GLuint _viewTransformId;
	Model *_model;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader, Model *model);

	~ShaderProgram();

	void LinkShaders();
	void Use();
};
