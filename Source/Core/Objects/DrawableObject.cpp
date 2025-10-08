//
// Created by Petr Pavlík on 29.09.2025.
//

#include "DrawableObject.h"

void DrawableObject::SetModel(Model *model)
{
    this->_model = model;
    this->_model->Initialize(this);
}

void DrawableObject::OnRender()
{
    GameObject::OnRender();

    if (_model != nullptr) _model->Draw();
}

