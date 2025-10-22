//
// Created by Petr Pavlík on 22.09.2025.
//

#include "ShaderProgram.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../Application.h"
#include "Core/logger.h"
#include "Core/ObjectComponents/ModelComponent.h"


ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
}

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader, Transform *modelTransfrom)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
    this->_modelTransform = modelTransfrom;
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::LinkShaders()
{
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _fragmentShader->GetShaderID());
    glAttachShader(_shaderProgram, _vertexShader->GetShaderID());
    glLinkProgram(_shaderProgram);

    _modelTransformId = glGetUniformLocation(_shaderProgram, "modelMatrix");
    _projectionTransformId = glGetUniformLocation(_shaderProgram, "projectionMatrix");
    _viewTransformId = glGetUniformLocation(_shaderProgram, "viewMatrix");
    _cameraLocationId = glGetUniformLocation(_shaderProgram, "cameraWorldLocation");

    GLint status;
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(_shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void ShaderProgram::Use()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();

    if (camera == nullptr) return;

    SendInt("lightCount", 1);
    SendVec4("lights[0].position", glm::vec4(0, 3, 0, 1));

    glUseProgram(_shaderProgram);

    glUniformMatrix4fv(_modelTransformId, 1, GL_FALSE, &_modelTransform->AsMatrix()[0][0]);
    glUniformMatrix4fv(_viewTransformId, 1, GL_FALSE, &camera->GetCameraViewMatrix()[0][0]);
    glUniformMatrix4fv(_projectionTransformId, 1, GL_FALSE, &(camera->GetCameraProjectionMatrix())[0][0]);

    float cameraPos[3] = {
        camera->GetWorldLocation().GetX(),
        camera->GetWorldLocation().GetY(),
        camera->GetWorldLocation().GetZ()
    };
    glUniform3fv(_cameraLocationId, 1, cameraPos);
}

void ShaderProgram::SendVec4(const std::string &destination, const glm::vec4 &value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgram, destination.c_str());
    if (variableDestination < 0)
    {
        LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgram);
        glUniform4f(variableDestination, value.x, value.y, value.z, value.w);
    }
}

void ShaderProgram::SendInt(const std::string &destination, const int value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgram, destination.c_str());
    if (variableDestination < 0)
    {
        LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgram);
        glUniform1i(variableDestination, value);
        //glUseProgram(0);
    }
}

void ShaderProgram::Dispose()
{
    glDeleteProgram(_shaderProgram);
}
