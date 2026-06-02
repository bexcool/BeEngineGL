//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerCharacter.h"

#include "BECore/Controllers/PlayerController.h"
#include "BECore/ObjectComponents/CharacterCollisionComponent.h"

PlayerCharacter::PlayerCharacter()
{
    SetController(std::make_unique<PlayerController>());

    _characterCollision = new CharacterCollisionComponent(0.6f, 0.2f);
    AddComponent(_characterCollision);
}
