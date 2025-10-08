//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include <glm/detail/func_trigonometric.inl>

#include "../Core/Application.h"
#include "../Core/Events/InputManager.h"

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

void TestLevel::OnLoaded() {}
void TestLevel::OnUnloaded() {}
void TestLevel::OnRendered() {}

void TestLevel::CheckMovementInput()
{
    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();
    auto camerLoc = camera->GetWorldLocation();
    auto camerRot = camera->GetWorldRotation();

    float yaw = camerRot.GetYaw(),
            pitch = camerRot.GetPitch();

    Location camLocation = camera->GetWorldLocation();

    float deltaTime = Application::GetInstance()->GetDeltaTime();

    double xpos, ypos;
    glfwGetCursorPos(Application::GetInstance()->GetWindow()->AsGLFWWindow(), &xpos, &ypos);

    glm::vec3 front = camera->GetLookTargetLocation();

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
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(front);

        camera->SetLookTargetLocation(Location(
            front.x,
            front.y,
            front.z
        ));

        camera->SetWorldRotation(Rotation(0, pitch, yaw));
    }

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W))
    {
        camLocation += speed * deltaTime * front;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S))
    {
        camLocation -= speed * deltaTime * front;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A))
    {
        camLocation -= speed * deltaTime * right;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D))
    {
        camLocation += speed * deltaTime * right;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE))
    {
        camLocation.y += speed * deltaTime;
    }

    if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER))
    {
        camLocation.y -= speed * deltaTime;
    }


    lastX = xpos;
    lastY = ypos;

    camera->SetWorldLocation(camLocation);
}

void TestLevel::OnTick()
{
    CheckMovementInput();
}
