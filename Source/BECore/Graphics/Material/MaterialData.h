//
// Created by Petr Pavlík on 28.11.2025.
//

#pragma once
#include "BoolMaterialParameter.h"
#include "MaterialParameter.h"
#include "EngineResources/Assets/Textures/TEX_Default.h"

struct MaterialData
{
    MaterialParameter diffuse = MaterialParameter(TEX_Default());
    MaterialParameter shininess = MaterialParameter(1.0f);
    MaterialParameter emission = MaterialParameter(0.0f);
    BoolMaterialParameter rendererDisableFaceCulling = BoolMaterialParameter(false);
};
