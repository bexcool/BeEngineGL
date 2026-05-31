//
// Created by Petr Pavlík on 26.11.2025.
//

#pragma once
#include "BECore/Graphics/Material/Texture.h"

class TEX_Default : public Texture
{
public:
    TEX_Default()
    {
        this->_path = "./EngineResources/Assets/Textures/DefaultTexture.png";
    }
};
