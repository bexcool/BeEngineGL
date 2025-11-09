//
// Created by Petr Pavlík on 08.11.2025.
//

#include "SkyBoxShaderProgram.h"

#include "Core/Application.h"
#include "Libs/stb_image.h"

void SkyBoxShaderProgram::Use()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();

    if (camera == nullptr) return;

    glUseProgram(_shaderProgramId);

    SendInt("useTexture", _shaderInfo.useTexture);
    if (_shaderInfo.useTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
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

void SkyBoxShaderProgram::CreateTextures()
{
    stbi_set_flip_vertically_on_load(false);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);

    int text_width, text_height, channels;
    unsigned char *data;
    data = stbi_load("./Resources/Assets/Textures/CubeMap/posx.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load("./Resources/Assets/Textures/CubeMap/negx.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load("./Resources/Assets/Textures/CubeMap/posy.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load("./Resources/Assets/Textures/CubeMap/negy.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load("./Resources/Assets/Textures/CubeMap/posz.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load("./Resources/Assets/Textures/CubeMap/negz.jpg", &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
