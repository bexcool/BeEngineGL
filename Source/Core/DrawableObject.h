//
// Created by Petr Pavlík on 29.09.2025.
//

#pragma once
#include "Graphics/Model.h"
#include "Graphics/ShaderProgram.h"
#include "Math/Transform.h"

class DrawableObject
{
private:
    Model *_model;
    Transform *_transform;

public:
    DrawableObject();

    DrawableObject(Transform *transform);

    void SetModel(Model *model);

    void Draw() const;

    Transform *GetTransform() { return _transform; }
};
