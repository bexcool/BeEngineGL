//
// Created by Petr Pavlík on 06.10.2025.
//

#include "Controller.h"

void Controller::SetOwner(GameObject *owner)
{
    _owner = owner;
}

void Controller::OnPossessed(GameObject *owner)
{
    SetOwner(owner);
}

DECLARE_VIRTUAL_COREEVENTS(Controller)
