//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include "DrawableObject.h"


class Level
{
private:
    vector<DrawableObject *> _drawableObjects;
    std::string _name;

public:
    Level(std::string name) : _name(name) {};

    ~Level();

    std::string GetName() { return _name; }

    void AddObject(DrawableObject *drawableObject);

    void RemoveObject(DrawableObject *drawableObject);

    vector<DrawableObject *> *GetDrawableObjects() { return &_drawableObjects; }
};
