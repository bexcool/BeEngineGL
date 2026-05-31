//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once

#include "TEX_Shrek.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/Material/MaterialData.h"
#include "BECore/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Shrek, (MaterialData{.diffuse = MaterialParameter(TEX_Shrek())}))
