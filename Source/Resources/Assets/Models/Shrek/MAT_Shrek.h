//
// Created by Petr Pavlík on 25.11.2025.
//

#pragma once

#include "TEX_Shrek.h"
#include "Core/Graphics/Material/Material.h"
#include "Core/Graphics/Material/MaterialParameter.h"

BE_MATERIAL(MAT_Shrek)
{
public:
    MAT_Shrek()
    {
        _diffuse = MaterialParameter(TEX_Shrek());
    }
};
