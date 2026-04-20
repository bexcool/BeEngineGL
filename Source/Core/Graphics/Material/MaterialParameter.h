//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include <glm/vec3.hpp>

#include "Texture.h"


class MaterialParameter
{
    glm::vec3 _value = glm::vec3(1);
    Texture _texture = DEFAULT_TEXTURE;

public:
    MaterialParameter() = default;
    explicit MaterialParameter(float scalar);
    explicit MaterialParameter(glm::vec3 value);
    explicit MaterialParameter(const Texture &texture);
    MaterialParameter(glm::vec3 value, const Texture &texture);

    [[nodiscard]] bool HasTexture();
    [[nodiscard]] glm::vec3 GetValue() const;
    [[nodiscard]] Texture GetTexture() const;
};

enum class MatParameterType
{
    Diffuse, Shininess, Emission
};
