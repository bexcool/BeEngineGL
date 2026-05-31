//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once
#include "MaterialParameter.h"


class BoolMaterialParameter : public MaterialParameter
{
    bool _value = false;

public:
    BoolMaterialParameter() = default;
    explicit BoolMaterialParameter(bool value);

    [[nodiscard]] bool GetValue() const;
};
