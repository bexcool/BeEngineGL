//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Application.h"

#include "../Resources/Models/suzi_flat.h"
#include "../Resources/Models/gift.h"
#include "Graphics/Renderer.h"
#include "../Game/TestLevel.h"
#include "../Resources/Models/suzi_smooth.h"
#include "logger.h"
#include "Events/InputManager.h"
#include "Game/MonkeyLevel.h"
#include "ObjectComponents/ModelComponent.h"
#include "Objects/Character/PlayerCharacter.h"

Application *Application::_currentApp = nullptr;

Application::Application(int width, int height, std::string title)
{
	this->_currentApp = this;
	this->_width = width;
	this->_height = height;
	this->_title = title;
}

void Application::Run()
{
	logger_init("app.log");
	LOG("Starting application...");

	_window = new Window(this->_width, this->_height, this->_title);

	_renderer = new Renderer(this->GetWindow()->AsGLFWWindow());

	_gameLoop = new GameLoop(_renderer);

	InputManager::Initialize();

	// Tests
	auto *level1 = new TestLevel("level1");

	LoadLevel(level1);

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

void Application::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
	if (e.Action == GLFW_PRESS)
	{
		switch (e.Key)
		{
			case GLFW_KEY_Y:
			{
				auto *level2 = new MonkeyLevel();

				LoadLevel(level2);

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
