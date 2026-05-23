//
// Created by Petr Pavlík on 14.10.2025.
//

#include "Model.h"

#include <iostream>
#include <memory>

#include "Core/logger.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "Libs/tiny_obj_loader.h"

std::unordered_map<std::string, Model::ModelCache> Model::ModelInstances;

Model::~Model() {
    return;

    if (_VBO)
        glDeleteBuffers(1, &_VBO);
    if (_VAO)
        glDeleteVertexArrays(1, &_VAO);
}

std::string Model::GetModelPath() {
    return _modelPath;
}

std::shared_ptr<Material> Model::GetMaterial() {
    return _material;
}

void Model::SetModel(const std::string& modelPath) {
    _modelPath = modelPath;
    SetModelCustomSP(modelPath);
}

void Model::SetModelCustomSP(const std::string& modelPath) {
    // Do not create new model, if the old one exists
    auto foundModel = ModelInstances.find(modelPath);
    if (foundModel != ModelInstances.end()) {
        const auto& existingModel = foundModel->second;

        _modelPath = existingModel.modelPath;
        _VBO = existingModel.VBO;
        _VAO = existingModel.VAO;
        _amountOfVertices = existingModel.amountOfVertices;

        LOG("Model already exists. Referencing data... Path: %s, VBO: %d, VAO: %d", modelPath.c_str(), _VBO, _VAO);

        return;
    }

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

    size_t totalIndices = 0;
    for (const auto& shape : shapes) {
        totalIndices += shape.mesh.indices.size();
    }

    std::vector<float> vertices;

    vertices.reserve(totalIndices * 8);

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            } else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            } else {
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
    glGenVertexArrays(1, &_VAO);   // generate the VAO
    glBindVertexArray(_VAO);       // bind the VAO
    glEnableVertexAttribArray(0);  // enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);  // enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);  // enable vertex attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    LOG("Adding new model geometry to global cache: %s", modelPath.c_str());

    ModelCache newCache{
        .VAO = _VAO,
        .VBO = _VBO,
        .amountOfVertices = _amountOfVertices,
        .modelPath = _modelPath};

    ModelInstances[modelPath] = newCache;
}

void Model::SetModel(const std::string& modelPath, std::shared_ptr<Material> material) {
    _modelPath = modelPath;
    _material = material;
    _shaderProgram = _material->GetShaderProgram();

    SetModel(modelPath);
}

void Model::SetModelCustomSP(const std::string& modelPath, const Material& material) {
    _modelPath = modelPath;
    _material = std::make_shared<Material>(material);

    SetModelCustomSP(modelPath);
}

void Model::Render(const Transform& transform) {
    *_transform = transform;

    _material->GetShaderProgram()->Use(_material.get(), _transform);
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _amountOfVertices);
}
