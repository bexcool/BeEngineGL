//
// Created by Petr Pavlík on 14.10.2025.
//

#pragma once
#include "Shader.h"
#include "ShaderInfo.h"
#include "ShaderProgram.h"

#define LEGACY_GEN_MODEL_HEADER_SI(className, modelData, shaderInfoData) \
class className : public Model\
{\
    public:\
className()\
    {\
        SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), shaderInfoData);\
    }\
className(const ShaderInfo &shaderInfo)\
{\
    SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), shaderInfo);\
}\
};

#define LEGACY_GEN_MODEL_HEADER(className, modelData) \
class className : public Model\
{\
public:\
className()\
{\
SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), ShaderInfo("Resources/Shaders/phong.frag"));\
}\
className(const ShaderInfo &shaderInfo)\
{\
SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), shaderInfo);\
}\
};

class Model
{
    Shader *_fragmentShader, *_vertexShader;
    ShaderInfo _shaderInfo = ShaderInfo();
    ShaderProgram *_shaderProgram;
    unsigned int _amountOfVertices;
    GLuint _VAO = 0, _VBO = 0;

    std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

    void LinkShaderProgram();

public:
    Model() = default;
    ~Model();

    void SetModel(std::string modelPath);
    void SetModel(std::string modelPath, const ShaderInfo &shaderInfo);
    void SetModel(const float *vertices, unsigned int amount);
    void SetModel(const float *vertices, unsigned int amount, const ShaderInfo &shaderInfo);

    void Render(const Transform &transform);
};
