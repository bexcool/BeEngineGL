#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "EngineResources/Assets/Textures/TEX_Default.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"
#include "EngineResources/Assets/Textures/TEX_Moon.h"

BE_MATERIAL(MAT_Moon, (MaterialData{.diffuse = MaterialParameter(TEX_Moon()),
                .shininess = MaterialParameter(0)}))
