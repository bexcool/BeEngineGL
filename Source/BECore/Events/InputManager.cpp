//
// Created by Petr Pavlík on 06.10.2025.
//

#include "InputManager.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_set>

#include "MouseKeyEventArgs.h"
#include "../Application.h"

std::unordered_set<int> InputManager::_pressedKeyboardKeys;
std::unordered_set<int> InputManager::_pressedMouseKeys;

void KeyboardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) InputManager::GetPressedKeyboardKeys()->insert(key);
    else if (action == GLFW_RELEASE) InputManager::GetPressedKeyboardKeys()->erase(key);
    Application::GetInstance()->OnKeyboardKeyEvent(KeyboardKeyEventArgs(key, scancode, action, mods));
}

void MouseKeyCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) InputManager::GetPressedMouseKeys()->insert(button);
    else if (action == GLFW_RELEASE) InputManager::GetPressedMouseKeys()->erase(button);
    Application::GetInstance()->OnMouseKeyEvent(MouseKeyEventArgs(button, action, mods));
}

void InputManager::Initialize()
{
    glfwSetKeyCallback(Application::GetInstance()->GetWindow()->AsGLFWWindow(), KeyboardKeyCallback);
    glfwSetMouseButtonCallback(Application::GetInstance()->GetWindow()->AsGLFWWindow(), MouseKeyCallback);
}

std::unordered_set<int> *InputManager::GetPressedKeyboardKeys()
{
    return &_pressedKeyboardKeys;
}

std::unordered_set<int> *InputManager::GetPressedMouseKeys()
{
    return &_pressedMouseKeys;
}

bool InputManager::IsKeyboardKeyPressed(const int key)
{
    return _pressedKeyboardKeys.contains(key);
}

bool InputManager::IsMouseKeyPressed(int key)
{
    return _pressedMouseKeys.contains(key);
}
