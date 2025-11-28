//
// Created by Petr Pavlík on 25.11.2025.
//

#include "MaterialParameter.h"

MaterialParameter::MaterialParameter(const glm::vec3 value)
{
    _value = value;
    _texture = EMPTY_TEXTURE;
}

MaterialParameter::MaterialParameter(const Texture &texture)
{
    _texture = texture;
}

MaterialParameter::MaterialParameter(const glm::vec3 value, const Texture &texture)
{
    _value = value;
    _texture = texture;
}

bool MaterialParameter::HasTexture()
{
    return !_texture.GetPath().empty();
}

glm::vec3 MaterialParameter::GetValue() const
{
    return _value;
}

Texture MaterialParameter::GetTexture() const
{
    return _texture;
}
