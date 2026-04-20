#pragma once

#include "Core/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Wood.h"

BE_MATERIAL(MAT_Wood, (MaterialData{
                .diffuse = MaterialParameter(TEX_Wood()),
                .shininess = MaterialParameter(0),
                .emission = MaterialParameter(3)}
            ))
