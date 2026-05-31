//
// Created by Petr Pavlík on 27.10.2025.
//

#pragma once
#include "BECore/Graphics/Model.h"

BE_MODEL(MOD_SkyBox, "./EngineResources/Assets/Models/cube.obj", std::make_shared<Material>("MAT_SkyBox" ,ShaderInfo{
             .fragmentShaderPath = "./EngineResources/Shaders/skybox.frag.glsl"
             }))
