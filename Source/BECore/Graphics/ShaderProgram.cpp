//
// Created by Petr Pavlík on 22.09.2025.
//

#include "ShaderProgram.h"

#include <utility>

#include "../Application.h"
#include "BECore/ObjectComponents/ModelComponent.h"
#include "BECore/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"

ShaderProgram::ShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
}

ShaderProgram::ShaderProgram(const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader, Material *material)
{
    this->_vertexShader = vertexShader;
    this->_fragmentShader = fragmentShader;
    this->_material = material;
}

ShaderProgram::~ShaderProgram()
{
    if (_shaderProgramId)
    {
        glDeleteProgram(_shaderProgramId);
        _shaderProgramId = 0;
    }
}

void ShaderProgram::SetMaterial(Material *material)
{
    this->_material = material;
}

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

        glDetachShader(_shaderProgramId, _vertexShader->GetShaderID());
        glDetachShader(_shaderProgramId, _fragmentShader->GetShaderID());
        glDeleteProgram(_shaderProgramId);

        _shaderProgramId = 0;
    }
}

void ShaderProgram::CreateTextures()
{
    // Load texture
    int text_width, text_height, channels;

    stbi_set_flip_vertically_on_load(true);

    auto texDiffuseParam = _material->GetParameter(MatParameterType::Diffuse);
    if (texDiffuseParam->HasTexture())
    {
        auto path = texDiffuseParam->GetTexture().GetPath();

        unsigned char *data = stbi_load(path.c_str(), &text_width, &text_height, &channels, 4);
        if (!data)
        {
            LOG_E("Error loading texture: %", path.c_str());
        }

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        texDiffuseParam->GetTexture().GetOptions().filterUseNearest ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                        texDiffuseParam->GetTexture().GetOptions().filterUseNearest ? GL_NEAREST : GL_LINEAR); // GL_LINEAR

        stbi_image_free(data);
    }
}

void ShaderProgram::Use()
{
    Use(_material, nullptr);
}

void ShaderProgram::Use(const Material *material, const std::shared_ptr<Transform> &modelTransform)
{
    auto level = Application::GetInstance()->GetLevel();
    auto camera = level->GetActiveCamera();

    if (camera == nullptr || material == nullptr || modelTransform == nullptr)
        return;

    int lightsWithNonZeroIntensity = 0;
    auto lights = level->GetLightComponents();

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

    SendFloat("skyLightIntensity", level->GetSkyLightIntensity());

    SendVec4("ambient", glm::vec4(0.05, 0.05, 0.05, 1));

    // Difuse
    auto diffuse_value = material->GetParameter(MatParameterType::Diffuse)->GetValue();
    SendVec4("diffuse_value", glm::vec4(diffuse_value, 1));

    auto texDiffuseParam = material->GetParameter(MatParameterType::Diffuse);
    SendInt("diffuse_useTexture", texDiffuseParam->HasTexture());

    if (texDiffuseParam->HasTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        SendInt("diffuse_texture2D", 0);
    }

    // Shininess
    auto shininess_value = material->GetParameter(MatParameterType::Shininess)->GetValue();
    SendVec3("shininess_value", shininess_value);

    // Emission
    auto emission_value = material->GetParameter(MatParameterType::Emission)->GetValue();
    SendVec3("emission_value", emission_value);

    glUniformMatrix4fv(_modelTransformId, 1, GL_FALSE, &modelTransform->AsMatrix()[0][0]);
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
        // LOG_W("The variable %s does not exist.", destination.c_str());
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
        // LOG_W("The variable %s does not exist.", destination.c_str());
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
        // LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1ui(variableDestination, value);
        // glUseProgram(0);
    }
}

void ShaderProgram::SendInt(const std::string &destination, const int value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        // LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1i(variableDestination, value);
        // glUseProgram(0);
    }
}

void ShaderProgram::SendFloat(const std::string &destination, const float value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        // LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1f(variableDestination, value);
        // glUseProgram(0);
    }
}

void ShaderProgram::SendBool(const std::string &destination, const bool value) const
{
    GLint variableDestination = glGetUniformLocation(this->_shaderProgramId, destination.c_str());
    if (variableDestination < 0)
    {
        // LOG_W("The variable %s does not exist.", destination.c_str());
    } else
    {
        glUseProgram(this->_shaderProgramId);
        glUniform1i(variableDestination, value);
        // glUseProgram(0);
    }
}
