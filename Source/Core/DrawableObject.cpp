//
// Created by Petr Pavlík on 29.09.2025.
//

#include "DrawableObject.h"

DrawableObject::DrawableObject(Model *model)
{
    this->_model = model;
    this->_transform = new Transform();
}

DrawableObject::DrawableObject(Model *model, Transform *transform)
{
    this->_model = model;
    this->_transform = transform;
}

void DrawableObject::Draw() const
{
    _model->Draw();
}

