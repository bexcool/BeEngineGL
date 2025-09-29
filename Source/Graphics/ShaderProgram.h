//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"

class ShaderProgram
{
private:
	GLuint _shaderProgram;
	Shader *_vertexShader;
	Shader *_fragmentShader;
	GLuint _modelTransformId;
	glm::mat4 _tmpMatrix;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	~ShaderProgram();

	GLuint GetShaderProgramID() { return _shaderProgram; };


	void LinkShaders();

	void Use();
};
