#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"
#include "EngineResources/Assets/Textures/TEX_Grass.h"

BE_MATERIAL(MAT_Grass, (MaterialData{.diffuse = MaterialParameter(TEX_Grass()), .shininess = MaterialParameter(0), .rendererDisableFaceCulling = BoolMaterialParameter(true)}))
