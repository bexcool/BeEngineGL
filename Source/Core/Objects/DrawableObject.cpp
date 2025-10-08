//
// Created by Petr Pavlík on 29.09.2025.
//

#include "DrawableObject.h"

DrawableObject::DrawableObject(Transform *transform)
{
    this->_transform = transform;
}

void DrawableObject::SetModel(Model *model)
{
    this->_model = model;
    this->_model->Initialize(this);
}


void DrawableObject::Draw() const
{
    if (_model != nullptr) _model->Draw();
}

