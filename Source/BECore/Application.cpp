//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Application.h"

#include "Events/InputManager.h"
#include "Game/BallsLevel.h"
#include "Graphics/Renderer.h"
#include "ObjectComponents/ModelComponent.h"
#include "logger.h"

Application *Application::_currentApp = nullptr;

Application::Application(int width, int height, std::string title)
{
    this->_currentApp = this;
    this->_width = width;
    this->_height = height;
    this->_title = title;
}

void Application::Run(Level *initialLevel)
{
    logger_init("app.log");
    LOG("Starting application...");

    _physicsEngine = new PhysicsEngine();
    _physicsEngine->Initialize();

    _window = new Window(this->_width, this->_height, this->_title);

    // Sets cursor state to locked
    SetCursorState(false, true);

    _renderer = new Renderer(this->GetWindow()->AsGLFWWindow());

    _gameLoop = new GameLoop(_renderer);

    InputManager::Initialize();

    LoadLevel(initialLevel);

    _gameLoop->Start();
}

void Application::SetCursorState(bool isVisible, bool isLocked)
{
    _isCursorVisible = isVisible;
    _isCursorLocked = isLocked;

    glfwSetInputMode(_window->AsGLFWWindow(), GLFW_CURSOR, _isCursorLocked ? GLFW_CURSOR_DISABLED : (_isCursorVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN));
}

void Application::SetCursorState(const CursorState &state)
{
    SetCursorState(state.visible, state.locked);
}

CursorState Application::GetCursorState()
{
    int value = glfwGetInputMode(_window->AsGLFWWindow(), GLFW_CURSOR);

    switch (value)
    {
        case GLFW_CURSOR_NORMAL:
            _isCursorVisible = true;
            _isCursorLocked = false;
            break;
        case GLFW_CURSOR_HIDDEN:
            _isCursorVisible = false;
            _isCursorLocked = false;
            break;
        case GLFW_CURSOR_DISABLED:
            _isCursorVisible = false;
            _isCursorLocked = true;
            break;
        default: break;
    }

    return {_isCursorVisible, _isCursorLocked};
}

void Application::LoadLevel(Level *level)
{
    _requestedLevel = level;
}

float Application::GetDeltaTime()
{
    return _gameLoop->GetDeltaTime();
}

float Application::GetTime()
{
    return glfwGetTime();
}

void Application::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    if (e.Action == GLFW_RELEASE)
    {
        switch (e.Key)
        {
            case GLFW_KEY_ESCAPE:
            {
                if (GetCursorState().locked)
                    SetCursorState(true, false);
                else
                {
                    SetCursorState(false, true);
                }

                break;
            }
        }
    }

    GetLevel()->OnKeyboardKeyEvent(e);
}

void Application::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    GetLevel()->OnMouseKeyEvent(e);
}

void Application::OnRender() {}

void Application::OnTick()
{
    if (_requestedLevel != nullptr)
    {
        // Call on OnUnloaded
        if (_currentLevel != nullptr) _currentLevel->OnUnloaded();
        // Switch to new level
        _currentLevel = _requestedLevel;
        _requestedLevel = nullptr;

        _currentLevel->OnLoaded();
    }

    if (_currentLevel != nullptr) _currentLevel->OnTick();
}
