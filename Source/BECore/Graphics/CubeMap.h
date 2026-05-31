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
    "./Resources/Assets/Textures/CubeMap/posx.jpg",
    "./Resources/Assets/Textures/CubeMap/negx.jpg",
    "./Resources/Assets/Textures/CubeMap/posy.jpg",
    "./Resources/Assets/Textures/CubeMap/negy.jpg",
    "./Resources/Assets/Textures/CubeMap/posz.jpg",
    "./Resources/Assets/Textures/CubeMap/negz.jpg"
};
