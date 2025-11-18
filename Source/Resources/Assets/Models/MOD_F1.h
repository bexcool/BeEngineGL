//
// Created by Petr Pavlík on 27.10.2025.
//

#pragma once
#include "Core/Graphics/Model.h"

class MOD_F1 : public Model
{
public:
    MOD_F1() { SetModel("Resources/Assets/Models/formula1.obj", ShaderInfo{.useTexture = true}); }
    MOD_F1(const ShaderInfo &shaderInfo) { SetModel("Resources/Assets/Models/formula1.obj", shaderInfo); }
};
