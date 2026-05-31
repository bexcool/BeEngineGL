#pragma once

#include "TEX_Toilet.h"
#include "BECore/Graphics/Material/Texture.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Toilet, (MaterialData{.diffuse = MaterialParameter(TEX_Toilet()), .shininess = MaterialParameter(0)}))
