//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerController.h"

#include "Core/Events/InputManager.h"
#include "Core/Application.h"
#include <typeinfo>

#include "Core/logger.h"
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

    if (e.Button == GLFW_MOUSE_BUTTON_LEFT && e.Action == GLFW_RELEASE)
    {
        auto window = Application::GetInstance()->GetWindow();

        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        GLint x = (GLint) GetMousePosition().x;
        GLint y = (GLint) GetMousePosition().y;

        double mx, my;
        glfwGetCursorPos(window->AsGLFWWindow(), &mx, &my);

        int fbw, fbh;
        glfwGetFramebufferSize(window->AsGLFWWindow(), &fbw, &fbh);

        mx *= (double) fbw / window->GetWidth();
        my *= (double) fbh / window->GetHeight();

        GLint xFinal = (int) mx, yFinal = (int) my;

        glReadPixels(xFinal, yFinal, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(xFinal, yFinal, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(xFinal, yFinal, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        LOG_W("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth%f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

        auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();
        //Můžeme nastavit vybrané těleso scena->setSelect(index-1);
        //Můžeme vypočíst pozici v globálním souřadném systému.
        glm::vec3 screenX = glm::vec3(xFinal, yFinal, depth);
        glm::mat4 view = camera->GetCameraViewMatrix();
        glm::mat4 projection = camera->GetCameraProjectionMatrix();
        glm::vec4 viewPort = glm::vec4(0, 0, window->GetWidth(), window->GetHeight());
        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

        printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
    }
}
