//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include <glm/detail/func_trigonometric.inl>

#include "../Core/Application.h"
#include "../Core/Events/InputManager.h"
#include "../Resources/Models/suzi_flat.h"
#include "Core/Objects/Character/PlayerCharacter.h"

double lastX = 400, lastY = 300;
float speed = 1;


void TestLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);

    if (e.Key == GLFW_KEY_LEFT_SHIFT)
    {
        if (e.Action == GLFW_PRESS) speed = 3;
        else if (e.Action == GLFW_RELEASE) speed = 1;
    }
}

void TestLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}

void TestLevel::OnLoaded()
{
    auto suziTrans = Transform(
        Location(10, 0, 0),
        Rotation(),
        Scale(0.5f)
    );
    auto suziObject = new DrawableObject();

    auto suziModel = new Model(suziFlat, sizeof(suziFlat) / (sizeof(float) * 6));
    suziObject->SetModel(suziModel);

    this->SpawnGameObject(suziObject, suziTrans);

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);
}

void TestLevel::OnUnloaded() {}
void TestLevel::OnRendered() {}

void TestLevel::OnTick()
{
    Level::OnTick();

    CheckMovementInput();
}
