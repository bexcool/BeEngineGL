//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerCharacter.h"

#include "BECore/Controllers/PlayerController.h"
#include "BECore/Events/InputManager.h"
#include "BECore/ObjectComponents/ColliderComponent.h"

PlayerCharacter::PlayerCharacter()
{
    // Set default controller for PlayerCharacter
    SetController(std::make_unique<PlayerController>());
    // add a collider so player participates in character-style collisions
    AddComponent(new ColliderComponent(glm::vec3(0.5f, 1.0f, 0.5f), false, false, 1.0f, true));
}
