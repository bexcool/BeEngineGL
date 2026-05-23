//
// Created by Petr Pavlík on 27.10.2025.
//

#pragma once
#include "Core/Graphics/Model.h"

BE_MODEL(MOD_SkyBox, "./Resources/Assets/Models/cube.obj", std::make_shared<Material>("MAT_SkyBox" ,ShaderInfo{
             .fragmentShaderPath = "./Resources/Shaders/skybox.frag.glsl"
             }))
