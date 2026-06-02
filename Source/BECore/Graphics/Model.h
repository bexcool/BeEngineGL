//
// Created by Petr Pavlík on 14.10.2025.
//

#pragma once
#include "Shader.h"
#include "ShaderInfo.h"
#include "ShaderProgram.h"
#include "Material/Material.h"
#include <vector>
#include <map>

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

#define BE_MODEL(className, modelPath, material) \
class className : public Model\
{\
public:\
className()\
{\
SetModel(modelPath, material);\
}\
explicit className(std::shared_ptr<Material> __material)\
{\
SetModel(modelPath, __material);\
}\
};

class Model
{
protected:
    struct ModelCache
    {
        GLuint VAO = 0;
        GLuint VBO = 0;
        unsigned int amountOfVertices = 0;
        std::string modelPath;
    };

    std::string _modelPath;
    std::shared_ptr<Shader> _fragmentShader = nullptr, _vertexShader = nullptr;
    std::shared_ptr<Material> _material;
    std::shared_ptr<ShaderProgram> _shaderProgram;
    unsigned int _amountOfVertices = 0;
    GLuint _VAO = 0, _VBO = 0;

    std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

    static std::unordered_map<std::string, ModelCache> ModelInstances;

public:
    Model() = default;
    ~Model();

    std::string GetModelPath();
    std::shared_ptr<Material> GetMaterial();

    void SetModel(const std::string &modelPath);
    void SetModelCustomSP(const std::string &modelPath);
    void SetModel(const std::string &modelPath, std::shared_ptr<Material> material);
    void SetModelCustomSP(const std::string &modelPath, const Material &material);

    void Render(const Transform &transform);
    bool IsMeshValid();
};
