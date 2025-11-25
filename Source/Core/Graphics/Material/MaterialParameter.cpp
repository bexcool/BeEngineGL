//
// Created by Petr Pavlík on 25.11.2025.
//

#include "MaterialParameter.h"

MaterialParameter::MaterialParameter(const glm::vec4 value)
{
    _value = value;
}

MaterialParameter::MaterialParameter(const Texture &texture)
{
    _texture = texture;
}

MaterialParameter::MaterialParameter(const glm::vec4 value, const Texture &texture)
{
    _value = value;
    _texture = texture;
}

bool MaterialParameter::HasTexture() const
{
    return _texture.has_value();
}

const glm::vec4 &MaterialParameter::GetValue() const
{
    return _value;
}

const std::optional<Texture> &MaterialParameter::GetTexture() const
{
    return _texture;
}
