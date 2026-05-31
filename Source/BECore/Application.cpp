//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Application.h"

#include "../Game/TestLevel.h"
#include "Events/InputManager.h"
#include "Game/BallsLevel.h"
#include "Game/SolarSystemLevel.h"
#include "Graphics/Renderer.h"
#include "ObjectComponents/ColliderComponent.h"
#include "ObjectComponents/ModelComponent.h"
#include "Physics/PhysicsEngine.h"
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

    _renderer = new Renderer(this->GetWindow()->AsGLFWWindow());

    _gameLoop = new GameLoop(_renderer, _physicsEngine);

    InputManager::Initialize();

    LoadLevel(initialLevel);

    _gameLoop->Start();
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
    if (e.Action == GLFW_PRESS)
    {
        switch (e.Key)
        {
            case GLFW_KEY_Y:
            {
                auto *level = new SolarSystemLevel();

                LoadLevel(level);

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
