//
// Created by Petr Pavlík on 08.11.2025.
//

#include "SkyBoxShaderProgram.h"

#include "BECore/Application.h"
#include "Libs/stb_image.h"

void SkyBoxShaderProgram::Use()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();

    if (camera == nullptr) return;

    glUseProgram(_shaderProgramId);

    SendInt("useTexture", 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
    SendInt("texture2D", 0);

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

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);

    int text_width, text_height, channels;
    unsigned char *data;

    // "./EngineResources/Assets/Textures/CubeMap/posx.jpg"
    data = stbi_load(this->CubeMap.posx.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load(this->CubeMap.negx.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load(this->CubeMap.posy.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load(this->CubeMap.negy.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load(this->CubeMap.posz.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    data = stbi_load(this->CubeMap.negz.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
