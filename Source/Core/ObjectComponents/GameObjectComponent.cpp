//
// Created by Petr Pavlík on 08.10.2025.
//

#include "GameObjectComponent.h"

void GameObjectComponent::OnAttached(GameObject *parent)
{
    _parent = parent;
}
