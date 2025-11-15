//
// Created by Petr Pavlík on 22.09.2025.
//

#include "ShaderProgram.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../Application.h"
#include "Core/logger.h"
#include "Core/ObjectComponents/ModelComponent.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"

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

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader, const ShaderInfo &shaderInfo, Transform *modelTransfrom)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
    this->_shaderInfo = shaderInfo;
    this->_modelTransform = modelTransfrom;
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::LinkShaders()
{
    _shaderProgramId = glCreateProgram();
    glAttachShader(_shaderProgramId, _vertexShader->GetShaderID());
    glAttachShader(_shaderProgramId, _fragmentShader->GetShaderID());
    glLinkProgram(_shaderProgramId);

    _modelTransformId = glGetUniformLocation(_shaderProgramId, "modelMatrix");
    _projectionTransformId = glGetUniformLocation(_shaderProgramId, "projectionMatrix");
    _viewTransformId = glGetUniformLocation(_shaderProgramId, "viewMatrix");
    _cameraLocationId = glGetUniformLocation(_shaderProgramId, "cameraWorldLocation");

    GLint status;
    glGetProgramiv(_shaderProgramId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(_shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(_shaderProgramId, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

void ShaderProgram::CreateTextures()
{
    // Load texture
    int text_width, text_height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(_shaderInfo.texturePath.c_str(), &text_width, &text_height, &channels, 4);
    if (!data)
    {
        LOG_E("Error loading texture: %", _shaderInfo.texturePath.c_str());
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

void ShaderProgram::Use()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();

    if (camera == nullptr) return;

    int lightsWithNonZeroIntensity = 0;
    auto lights = Application::GetInstance()->GetLevel()->GetLightComponents();

    glUseProgram(_shaderProgramId);

    for (int i = 0; i < lights.size(); i++)
    {
        float worldIntensity = lights[i]->GetWorldIntensity();

        lightsWithNonZeroIntensity++;

        std::string position = "lights[";
        position.append(std::to_string(i));
        position.append("].position");
        SendVec4(position, glm::vec4(lights[i]->GetWorldLocation().AsVec3(), 1));

        std::string radius = "lights[";
        radius.append(std::to_string(i));
        radius.append("].radius");
        SendFloat(radius, lights[i]->GetLight().radius);

        std::string color = "lights[";
        color.append(std::to_string(i));
        color.append("].color");
        SendVec4(color, glm::vec4(worldIntensity, worldIntensity, worldIntensity, 1));

        if (!lights[i]->GetLight().isPointLight)
        {
            std::string spotDirection = "lights[";
            spotDirection.append(std::to_string(i));
            spotDirection.append("].spotDirection");
            SendVec3(spotDirection, lights[i]->GetWorldRotation().GetForwardVector());
        }
    }

    SendInt("lightCount", lightsWithNonZeroIntensity);

    // glm::vec4(0.385, 0.647, 0.812, 1.0)
    auto clr = _shaderInfo.color;
    SendVec4("color", clr);

    SendVec4("ambient", glm::vec4(0.05, 0.05, 0.05, 1));

    SendInt("useTexture", _shaderInfo.useTexture);
    if (_shaderInfo.useTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        SendInt("texture2D", 0);
    }

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
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform4f(variableDestination, value.x, value.y, value.z, value.w);
    }
}

void ShaderProgram::SendVec3(const std::string &destination, const glm::vec3 &value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform3f(variableDestination, value.x, value.y, value.z);
    }
}

void ShaderProgram::SendUint(const std::string &destination, const unsigned int value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1ui(variableDestination, value);
        //glUseProgram(0);
    }
}

void ShaderProgram::SendInt(const std::string &destination, const int value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1i(variableDestination, value);
        //glUseProgram(0);
    }
}

void ShaderProgram::SendFloat(const std::string &destination, const float value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1f(variableDestination, value);
        //glUseProgram(0);
    }
}

void ShaderProgram::SendBool(const std::string &destination, const bool value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        //LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1i(variableDestination, value);
        //glUseProgram(0);
    }
}

void ShaderProgram::Dispose()
{
    glDeleteProgram(_shaderProgramId);
}
