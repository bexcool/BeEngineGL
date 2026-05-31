#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Mars.h"

BE_MATERIAL(MAT_Mars, (MaterialData{.diffuse = MaterialParameter(TEX_Mars()),
                .shininess = MaterialParameter(0)}))
