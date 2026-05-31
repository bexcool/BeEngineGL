//
// Created by Petr Pavlík on 31.05.2026.
//

#include "BoolMaterialParameter.h"

BoolMaterialParameter::BoolMaterialParameter(bool value)
{
    _value = value;
}

bool BoolMaterialParameter::GetValue() const
{
    return _value;
}
