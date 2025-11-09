//
// Created by Petr Pavlík on 06.11.2025.
//

#pragma once
#include "../Model.h"


class SkyBoxModel : public Model
{
public:
    SkyBoxModel();

    void LinkShaderProgram();
    void Render();
};
