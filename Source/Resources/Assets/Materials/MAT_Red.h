#pragma once

#include "Core/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Red, (MaterialData{.diffuse = MaterialParameter(glm::vec3(1,0,0))}))
