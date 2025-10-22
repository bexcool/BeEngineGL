//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "../Math/Transform.h"
#include "Core/Interfaces/IDisposable.h"

class ModelComponent;

class ShaderProgram : public IDisposable
{
private:
	GLuint _shaderProgram;
	Shader *_vertexShader;
	Shader *_fragmentShader;
	GLuint _modelTransformId;
	GLuint _projectionTransformId;
	GLuint _viewTransformId;
	GLuint _cameraLocationId;
	Transform *_modelTransform;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader, Transform *modelTransform);

	~ShaderProgram() override;

	void LinkShaders();
	void Use();

	void SendVec4(const std::string &destination, const glm::vec4 &value) const;
	void SendInt(const std::string &destination, const int value) const;

	void Dispose() override;
};
