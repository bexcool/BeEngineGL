//
// Created by Petr Pavlík on 09.10.2025.
//

#include "MonkeyLevel.h"

#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/Objects/Character/PlayerCharacter.h"
#include "Resources/Models/gift.h"
#include "Resources/Models/suzi_smooth.h"

void MonkeyLevel::OnLoaded()
{
    Level::OnLoaded();

    auto suziObject = new GameObject();
    auto suziModel = new ModelComponent();
    suziModel->SetModel(suziSmooth, sizeof(suziSmooth) / (sizeof(float) * 6));
    suziObject->AddComponent(suziModel);

    this->SpawnGameObject(suziObject, Transform(
                              Location(),
                              Rotation(),
                              Scale(0.2f)
                          ));

    auto suziObject2 = new GameObject();
    auto suziModel2 = new ModelComponent();
    suziModel2->SetModel(gift, sizeof(gift) / (sizeof(float) * 6));
    suziObject2->AddComponent(suziModel2);
    this->SpawnGameObject(suziObject2, Transform(
                              Location(.5f, 0.0f, 0.0f),
                              Rotation(),
                              Scale(0.7f)
                          ));

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);
}

void MonkeyLevel::OnUnloaded()
{
    Level::OnUnloaded();
}

void MonkeyLevel::OnRendered()
{
    Level::OnRendered();
}

void MonkeyLevel::OnTick()
{
    Level::OnTick();
}

void MonkeyLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);
}

void MonkeyLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}
