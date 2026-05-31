#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "EngineResources/Assets/Textures/TEX_Default.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"
#include "EngineResources/Assets/Textures/TEX_Sun.h"

BE_MATERIAL(MAT_Sun, (MaterialData{.diffuse = MaterialParameter(TEX_Sun()),
                .emission = MaterialParameter(2.0f)}))
