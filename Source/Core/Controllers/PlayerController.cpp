//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerController.h"

#include "Core/Events/InputManager.h"
#include "Core/Application.h"
#include <typeinfo>

#include "Core/Objects/Character/Character.h"

void PlayerController::SetRun(bool isRunning)
{
    _isRunnig = isRunning;
}

void PlayerController::MovePlayer() const
{
    auto app = Application::GetInstance();
    auto ownerLocation = GetOwner()->GetWorldLocation();
    auto front = static_cast<Vector3>(app->GetLevel()->GetActiveCamera()->GetLookTargetLocation());
    float deltaTime = app->GetDeltaTime();

    if (auto *character = dynamic_cast<Character *>(GetOwner()))
    {
        float speed = _isRunnig ? character->GetRunSpeed() : character->GetWalkSpeed();
        Vector3 right(glm::normalize(glm::cross(front.AsVec3(), glm::vec3(0.0f, 1.0f, 0.0f))));

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W))
        {
            ownerLocation += front * speed * deltaTime;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S))
        {
            ownerLocation -= front * speed * deltaTime;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A))
        {
            ownerLocation -= right * speed * deltaTime;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D))
        {
            ownerLocation += speed * deltaTime * right;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE))
        {
            ownerLocation.SetY(ownerLocation.GetY() + speed * deltaTime);
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER))
        {
            ownerLocation.SetY(ownerLocation.GetY() - speed * deltaTime);
        }

        GetOwner()->SetWorldLocation(ownerLocation);
    }
}

void PlayerController::OnTick()
{
    Controller::OnTick();

    MovePlayer();
}

void PlayerController::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Controller::OnKeyboardKeyEvent(e);

    if (e.Key == GLFW_KEY_LEFT_SHIFT)
    {
        SetRun(e.Action == GLFW_PRESS);
    }
}

void PlayerController::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Controller::OnMouseKeyEvent(e);
}
