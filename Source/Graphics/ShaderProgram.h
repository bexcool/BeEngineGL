//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>

#include "Shader.h"

class ShaderProgram
{
private:
	GLuint _shaderProgram{};
	Shader *_vertexShader;
	Shader *_fragmentShader;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	~ShaderProgram();

	GLuint GetShaderProgramID() { return _shaderProgram; };


	void LinkShaders();

	void Use();
};
