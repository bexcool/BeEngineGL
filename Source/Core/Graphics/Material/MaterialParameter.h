//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include <glm/vec4.hpp>

#include "Texture.h"


class MaterialParameter
{
    glm::vec4 _value = glm::vec4(1, 1, 1, 0);
    std::optional<Texture> _texture = DEFAULT_TEXTURE;

public:
    MaterialParameter() = default;
    explicit MaterialParameter(glm::vec4 value);
    explicit MaterialParameter(const Texture &texture);
    MaterialParameter(glm::vec4 value, const Texture &texture);

    [[nodiscard]] bool HasTexture() const;
    [[nodiscard]] const glm::vec4 &GetValue() const;
    [[nodiscard]] const std::optional<Texture> &GetTexture() const;
};
