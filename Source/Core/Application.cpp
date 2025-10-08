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
#include "ObjectComponents/ModelComponent.h"

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
	// Call on OnUnloaded
	if (_currentLevel != nullptr) _currentLevel->OnUnloaded();
	// Switch to new level
	_currentLevel = level;
	_currentLevel->OnLoaded();
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
				TestLevel *level2 = new TestLevel("level2");
				auto suziObject = new GameObject();
				auto suziModel = new ModelComponent();
				suziModel->SetModel(suziSmooth, sizeof(suziSmooth) / (sizeof(float) * 6));
				suziObject->AddComponent(suziModel);

				level2->SpawnGameObject(suziObject, Transform(
					                        Location(),
					                        Rotation(),
					                        Scale(0.2f)
				                        ));

				auto suziObject2 = new GameObject();
				auto suziModel2 = new ModelComponent();
				suziModel2->SetModel(gift, sizeof(gift) / (sizeof(float) * 6));
				suziObject2->AddComponent(suziModel2);
				level2->SpawnGameObject(suziObject2, Transform(
					                        Location(.5f, 0.0f, 0.0f),
					                        Rotation(),
					                        Scale(0.7f)
				                        ));

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
