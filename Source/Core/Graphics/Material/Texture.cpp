//
// Created by Petr Pavlík on 25.11.2025.
//

#include "Texture.h"

Texture::Texture(std::string path)
{
    this->_path = std::move(path);
}

std::string Texture::GetPath()
{
    return _path;
}
