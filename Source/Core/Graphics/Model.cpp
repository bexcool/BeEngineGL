//
// Created by Petr Pavlík on 14.10.2025.
//

#include "Model.h"

#include <iostream>

#include "Core/logger.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "Libs/tiny_obj_loader.h"

void Model::LinkShaderProgram()
{
    _vertexShader = new Shader(GL_VERTEX_SHADER, _shaderInfo.vertexShaderPath);
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, _shaderInfo.fragmentShaderPath);
    _fragmentShader->Compile();

    _shaderProgram = new ShaderProgram(_vertexShader, _fragmentShader, _shaderInfo, _transform.get());
    _shaderProgram->LinkShaders();
    if (_shaderInfo.useTexture) _shaderProgram->CreateTextures();
}

Model::~Model()
{
    return;

    delete _vertexShader;
    delete _fragmentShader;

    if (_VBO)
        glDeleteBuffers(1, &_VBO);
    if (_VAO)
        glDeleteVertexArrays(1, &_VAO);
}

ShaderInfo Model::GetShaderInfo()
{
    return _shaderInfo;
}

std::string Model::GetModelPath()
{
    return _modelPath;
}

void Model::SetModel(std::string modelPath)
{
    _modelPath = modelPath;
    SetModelCustomSP(modelPath);

    LinkShaderProgram();
}

void Model::SetModelCustomSP(std::string modelPath)
{
    _modelPath = modelPath;
    std::filesystem::path filePath = modelPath;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    std::string matDir = filePath.parent_path().string() + "/";
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filePath.c_str(), matDir.c_str());

    if (!err.empty())
        LOG_E(err.c_str());
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    std::vector<float> vertices;

    for (const auto &shape: shapes)
    {
        for (const auto &index: shape.mesh.indices)
        {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0)
            {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            } else
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0)
            {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            } else
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    _VBO = 0;
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    _amountOfVertices = vertices.size() / 8;

    _VAO = 0;
    glGenVertexArrays(1, &_VAO); //generate the VAO
    glBindVertexArray(_VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2); //enable vertex attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
}

void Model::SetModel(const std::string &modelPath, const ShaderInfo &shaderInfo)
{
    _modelPath = modelPath;
    _shaderInfo = shaderInfo;

    SetModel(modelPath);
}

void Model::SetModelCustomSP(std::string modelPath, const ShaderInfo &shaderInfo)
{
    _modelPath = modelPath;
    _shaderInfo = shaderInfo;

    SetModelCustomSP(modelPath);
}

void Model::SetModel(const float *vertices, unsigned int amount)
{
    _amountOfVertices = amount;

    //vertex buffer object (VBO)
    _VBO = 0;
    glGenBuffers(1, &_VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _amountOfVertices * sizeof(float) * 6, vertices, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    _VAO = 0;
    glGenVertexArrays(1, &_VAO); //generate the VAO
    glBindVertexArray(_VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));

    LinkShaderProgram();
}

void Model::SetModel(const float *vertices, unsigned int amount, const ShaderInfo &shaderInfo)
{
    _shaderInfo = shaderInfo;

    SetModel(vertices, amount);
}

void Model::Render(const Transform &transform)
{
    *_transform = transform;

    _shaderProgram->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
