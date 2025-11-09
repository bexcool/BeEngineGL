//
// Created by Petr Pavlík on 27.10.2025.
//

#pragma once
#include "Core/Graphics/Model.h"

GEN_MODEL_HEADER_SI(MOD_SkyBox, "./Resources/Assets/Models/cube.obj", (ShaderInfo{
                        .fragmentShaderPath = "./Resources/Shaders/skybox.frag"}))
