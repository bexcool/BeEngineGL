//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "../Events/CoreEvents.h"
#include "../Objects/GameObject.h"

class GameObject;

class Controller
{
private:
    GameObject *_owner;

    void SetOwner(GameObject *owner);

public:
    GameObject *GetOwner() const;

    virtual void OnPossessed(GameObject *owner);
    DEFINE_VIRTUAL_COREEVENTS
};
