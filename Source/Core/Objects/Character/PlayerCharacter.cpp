//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerCharacter.h"

#include "Core/Controllers/PlayerController.h"
#include "Core/Events/InputManager.h"

PlayerCharacter::PlayerCharacter()
{
    // Set default controller for PlayerCharacter
    SetController(std::make_unique<PlayerController>());
}
