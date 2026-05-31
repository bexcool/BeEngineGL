//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once
#include <string>

struct CubeMap
{
    std::string posx;
    std::string negx;
    std::string posy;
    std::string negy;
    std::string posz;
    std::string negz;
};

static const CubeMap DEFAULT_CUBEMAP{
    "./EngineResources/Assets/Textures/CubeMap/posx.jpg",
    "./EngineResources/Assets/Textures/CubeMap/negx.jpg",
    "./EngineResources/Assets/Textures/CubeMap/posy.jpg",
    "./EngineResources/Assets/Textures/CubeMap/negy.jpg",
    "./EngineResources/Assets/Textures/CubeMap/posz.jpg",
    "./EngineResources/Assets/Textures/CubeMap/negz.jpg"
};
