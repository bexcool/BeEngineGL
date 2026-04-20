#pragma once

#include "Core/Graphics/Material/Texture.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Grass.h"

BE_MATERIAL(MAT_Grass, (MaterialData{.diffuse = MaterialParameter(TEX_Grass()), .shininess = MaterialParameter(0)}))
