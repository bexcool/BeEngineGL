//
// Created by Petr Pavlík on 25.11.2025.
//

#include "Texture.h"

Texture::Texture(std::string path)
{
    this->_path = std::move(path);
}

Texture::Texture(std::string path, const TextureOptions &textureOptions)
{
    this->_path = std::move(path);
    this->_textureOptions = textureOptions;
}

const std::string Texture::GetPath() const
{
    return _path;
}

const TextureOptions Texture::GetOptions() const
{
    return _textureOptions;
}
