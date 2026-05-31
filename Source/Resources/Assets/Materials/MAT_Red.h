#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Red, (MaterialData{
                .diffuse = MaterialParameter(glm::vec3(1,0,0)),
                .shininess = MaterialParameter(8.0f)}))
