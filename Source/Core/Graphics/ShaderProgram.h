//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>

#include "../Math/Transform.h"
#include "Material/Material.h"
#include "Shader.h"

class ModelComponent;

class ShaderProgram {
   protected:
    GLuint _shaderProgramId = GL_NONE;
    std::shared_ptr<Shader> _vertexShader;
    std::shared_ptr<Shader> _fragmentShader;
    GLuint _modelTransformId = GL_NONE;
    GLuint _projectionTransformId = GL_NONE;
    GLuint _viewTransformId = GL_NONE;
    GLuint _cameraLocationId = GL_NONE;

    Material* _material = nullptr;
    GLuint _textureId = GL_NONE;

   public:
    ShaderProgram(const std::shared_ptr<Shader>& vertexShader, const std::shared_ptr<Shader>& fragmentShader);
    ShaderProgram(const std::shared_ptr<Shader>& vertexShader, const std::shared_ptr<Shader>& fragmentShader, Material* material);

    virtual ~ShaderProgram();

    void SetMaterial(Material* material);

    void LinkShaders();
    virtual void CreateTextures();
    virtual void Use();
    virtual void Use(const Material* material, const std::shared_ptr<Transform>& modelTransform);

    GLuint GetShaderProgramId() const {
        return _shaderProgramId;
    }

    void SendVec4(const std::string& destination, const glm::vec4& value) const;
    void SendVec3(const std::string& destination, const glm::vec3& value) const;
    void SendUint(const std::string& destination, unsigned int value) const;
    void SendInt(const std::string& destination, int value) const;
    void SendFloat(const std::string& destination, float value) const;
    void SendBool(const std::string& destination, bool value) const;
};
