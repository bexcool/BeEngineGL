//
// Created by Petr Pavlík on 06.11.2025.
//

#pragma once
#include "../Model.h"
#include "BECore/Graphics/CubeMap.h"


class SkyBoxModel : public Model
{
    CubeMap _cubeMap;

public:
    explicit SkyBoxModel(CubeMap cubeMap);

    void LinkShaderProgram();
    void Render();
};
