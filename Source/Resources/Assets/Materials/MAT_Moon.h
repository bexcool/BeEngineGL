#pragma once

#include "Core/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Moon.h"

BE_MATERIAL(MAT_Moon, (MaterialData{.diffuse = MaterialParameter(TEX_Moon()),
                .shininess = MaterialParameter(0)}))
