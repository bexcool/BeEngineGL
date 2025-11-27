//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include <glm/vec4.hpp>

#include "Texture.h"


class MaterialParameter
{
    glm::vec4 _value = glm::vec4(1, 1, 1, 1);
    Texture _texture = (Texture) DEFAULT_TEXTURE;

public:
    MaterialParameter() = default;
    explicit MaterialParameter(glm::vec4 value);
    explicit MaterialParameter(const Texture &texture);
    MaterialParameter(glm::vec4 value, const Texture &texture);

    [[nodiscard]] bool HasTexture();
    [[nodiscard]] const glm::vec4 &GetValue() const;
    [[nodiscard]] Texture GetTexture() const;
};

enum class MatParameterType
{
    Diffuse
};
