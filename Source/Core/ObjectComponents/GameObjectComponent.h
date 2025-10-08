//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../Objects/GameObject.h"

class GameObject;

class GameObjectComponent
{
    GameObject *_parent;

public:
    virtual void OnAttached(GameObject *parent);
    virtual void OnTick() {}
    virtual void OnRendered() {}
    virtual void OnRemovedFromParent() {}
};
