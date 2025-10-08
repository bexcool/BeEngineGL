//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerController.h"

#include "Core/Events/InputManager.h"
#include "Core/Application.h"
#include <typeinfo>

#include "Core/Objects/Character/Character.h"

void PlayerController::OnTick()
{
    Controller::OnTick();

    auto app = Application::GetInstance();
    auto ownerLocation = GetOwner()->GetWorldLocation();
    auto front = app->GetLevel()->GetActiveCamera()->GetLookTargetLocation();
    float deltaTime = app->GetDeltaTime();

    if (auto *character = dynamic_cast<Character *>(GetOwner()))
    {
        float speed = character->GetWalkSpeed();
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W))
        {
            ownerLocation += speed * deltaTime * front;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S))
        {
            ownerLocation -= speed * deltaTime * front;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A))
        {
            ownerLocation -= speed * deltaTime * right;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D))
        {
            ownerLocation += speed * deltaTime * right;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE))
        {
            ownerLocation.y += speed * deltaTime;
        }

        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER))
        {
            ownerLocation.y -= speed * deltaTime;
        }

        GetOwner()->SetWorldLocation(ownerLocation);
    }
}

void PlayerController::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Controller::OnKeyboardKeyEvent(e);
}

void PlayerController::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Controller::OnMouseKeyEvent(e);
}
