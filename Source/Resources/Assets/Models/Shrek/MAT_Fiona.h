#pragma once

#include "TEX_Fiona.h"
#include "Core/Graphics/Material/Texture.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialData.h"
#include "Core/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Fiona, (MaterialData{.diffuse = MaterialParameter(TEX_Fiona())}))
