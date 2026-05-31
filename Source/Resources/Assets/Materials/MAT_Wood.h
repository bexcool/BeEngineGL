#pragma once

#include "BECore/Graphics/Material/Texture.h"
#include "Resources/Assets/Textures/TEX_Default.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"
#include "Resources/Assets/Textures/TEX_Wood.h"

BE_MATERIAL(MAT_Wood, (MaterialData{
                .diffuse = MaterialParameter(TEX_Wood()),
                .shininess = MaterialParameter(0),
                .emission = MaterialParameter(3)}
            ))
