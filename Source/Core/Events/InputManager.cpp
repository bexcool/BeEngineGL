//
// Created by Petr Pavlík on 06.10.2025.
//

#include "InputManager.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../../Application.h"

void KeyPressCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application::GetInstance()->OnKeyEvent(KeyEventArgs(key, scancode, action, mods));
}

void InputManager::Initialize()
{
    glfwSetKeyCallback(Application::GetInstance()->GetWindow()->AsGLFWWindow(), KeyPressCallback);
}
