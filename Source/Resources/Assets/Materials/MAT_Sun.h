#pragma once

#include "Core/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Sun.h"

BE_MATERIAL(MAT_Sun, (MaterialData{.diffuse = MaterialParameter(TEX_Sun()),
                .emission = MaterialParameter(2.0f)}))
