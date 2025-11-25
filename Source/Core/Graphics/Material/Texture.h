//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include <string>
#include <utility>

class Texture
{
    std::string _path;

public:
    Texture() = default;
    ~Texture() = default;
    explicit Texture(std::string path);
};

static const Texture DEFAULT_TEXTURE("./Resources/Assets/Textures/DefaultTexture.png");
