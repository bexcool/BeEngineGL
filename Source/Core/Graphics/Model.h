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
SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), ShaderInfo());\
}\
className(const ShaderInfo &shaderInfo)\
{\
SetModel(modelData, sizeof(modelData) / (sizeof(float) * 6), shaderInfo);\
}\
};

#define GEN_MODEL_HEADER(className, modelPath) \
class className : public Model\
{\
public:\
className()\
{\
SetModel(modelPath, ShaderInfo());\
}\
className(const ShaderInfo &shaderInfo)\
{\
SetModel(modelPath, shaderInfo);\
}\
};

#define GEN_MODEL_HEADER_SI(className, modelPath, shaderInfoData) \
class className : public Model\
{\
public:\
className()\
{\
SetModel(modelPath, shaderInfoData);\
}\
className(const ShaderInfo &shaderInfo)\
{\
SetModel(modelPath, shaderInfo);\
}\
};

class Model
{
protected:
    std::string _modelPath;
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

    ShaderInfo GetShaderInfo();
    std::string GetModelPath();

    void SetModel(std::string modelPath);
    void SetModelCustomSP(std::string modelPath);
    void SetModel(const std::string &modelPath, const ShaderInfo &shaderInfo);
    void SetModelCustomSP(std::string modelPath, const ShaderInfo &shaderInfo);
    void SetModel(const float *vertices, unsigned int amount);
    void SetModel(const float *vertices, unsigned int amount, const ShaderInfo &shaderInfo);

    void Render(const Transform &transform);
};
