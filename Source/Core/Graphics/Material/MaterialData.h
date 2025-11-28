//
// Created by Petr Pavlík on 28.11.2025.
//

#pragma once
#include "MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Default.h"

struct MaterialData
{
    MaterialParameter diffuse = MaterialParameter(TEX_Default());
};
