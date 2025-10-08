//
// Created by Petr Pavlík on 06.10.2025.
//

#include "Controller.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../Application.h"

void Controller::SetOwner(GameObject *owner)
{
    _owner = owner;
}

GameObject *Controller::GetOwner() const
{
    return _owner;
}

void Controller::OnPossessed(GameObject *owner)
{
    SetOwner(owner);
}

glm::vec2 Controller::GetMousePosition()
{
    double x, y;
    glfwGetCursorPos(Application::GetInstance()->GetWindow()->AsGLFWWindow(), &x, &y);

    return {x, y};
}

glm::vec2 Controller::GetLastMousePosition()
{
    return _lastMousePosition;
}

void Controller::OnRender()
{
    CoreEvents::OnRender();
}

void Controller::OnTick()
{
    CoreEvents::OnTick();

    _lastMousePosition = GetMousePosition();
}

void Controller::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}

void Controller::OnMouseKeyEvent(MouseKeyEventArgs e) {}
