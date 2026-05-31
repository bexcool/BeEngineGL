//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once

#define BE_TEXTURE(className, path) \
    class className : public Texture \
    {\
    public:\
        className () { this->_path = path; }\
    };

#include <string>

class Texture
{
protected:
    std::string _path;

public:
    Texture() = default;
    ~Texture() = default;
    explicit Texture(std::string path);

    const std::string GetPath() const;
};

static const Texture DEFAULT_TEXTURE("./Resources/Assets/Textures/DefaultTexture.png");
static const Texture EMPTY_TEXTURE("");
