//
// Created by Petr Pavlík on 29.09.2025.
//

#include "DrawableObject.h"

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram)
{
    this->_model = model;
    this->_shaderProgram = shaderProgram;
    this->_transform = new Transform();
}
