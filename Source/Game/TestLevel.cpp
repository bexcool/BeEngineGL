//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include <glm/detail/func_trigonometric.inl>

#include "../Core/Application.h"
#include "../Core/Events/InputManager.h"

void TestLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}

void TestLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}

void TestLevel::OnLoaded() {}
void TestLevel::OnUnloaded() {}
void TestLevel::OnDraw() {}

float lastX = 400, lastY = 300;

void TestLevel::CheckMovementInput()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();
    auto camerLoc = camera->GetWorldLocation();
    auto camerRot = camera->GetWorldRotation();

    float x = camerLoc.GetX(),
            y = camerLoc.GetY(),
            z = camerLoc.GetZ(),
            yaw = camerRot.GetYaw(),
            pitch = camerRot.GetPitch();

    float deltaTime = Application::GetInstance()->GetDeltaTime();
    float speed = 1.0f;

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W))
    {
        x += speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S))
    {
        x -= speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A))
    {
        z -= speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D))
    {
        z += speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE))
    {
        y += speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER))
    {
        y -= speed * deltaTime;
    }

    double xpos, ypos;
    glfwGetCursorPos(Application::GetInstance()->GetWindow()->AsGLFWWindow(), &xpos, &ypos);

    if (InputManager::IsMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        float sensitivity = 0.1f;

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed: y-coordinates go from bottom to top

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // constrain pitch
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        glm::vec3 nFront = glm::normalize(front);

        camera->SetLookTargetLocation(Location(
            x + nFront.x,
            y + nFront.y,
            z + nFront.z
        ));

        camera->SetWorldRotation(Rotation(0, pitch, yaw));
    } else
    {
        lastX = xpos;
        lastY = ypos;
    }

    camera->SetWorldLocation(Location(x, y, z));
}

void TestLevel::OnTick()
{
    CheckMovementInput();
}
