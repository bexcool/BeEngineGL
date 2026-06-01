//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once

#define BE_TEXTURE(className, path, options) \
    class className : public Texture \
    {\
    public:\
        className () { this->_path = path; this->_textureOptions = options; }\
    };

#include <string>

#include "TextureOptions.h"

class Texture
{
protected:
    std::string _path;
    TextureOptions _textureOptions = TextureOptions();

public:
    Texture() = default;
    ~Texture() = default;
    explicit Texture(std::string path);
    explicit Texture(std::string path, const TextureOptions &textureOptions);

    [[nodiscard]] const std::string GetPath() const;
    [[nodiscard]] const TextureOptions GetOptions() const;
};

static const Texture DEFAULT_TEXTURE("./EngineResources/Assets/Textures/DefaultTexture.png");
static const Texture EMPTY_TEXTURE("");
