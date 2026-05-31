#pragma once

#include "TEX_Fiona.h"
#include "BECore/Graphics/Material/Texture.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Fiona, (MaterialData{.diffuse = MaterialParameter(TEX_Fiona()), .shininess = MaterialParameter(0.3)}))
