//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Level.h"

void Level::AddObject(DrawableObject *drawableObject)
{
    _drawableObjects.push_back(drawableObject);
}
