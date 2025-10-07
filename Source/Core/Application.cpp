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
	TestLevel *level1 = new TestLevel("level1");
	auto suziObject = new DrawableObject(new Transform(
		Location(10, 0, 0),
		Rotation(),
		Scale(0.5f)
	));

	auto suziModel = new Model(suziFlat, sizeof(suziFlat) / (sizeof(float) * 6));
	suziObject->SetModel(suziModel);

	level1->AddObject(suziObject);

	LoadLevel(level1);

	auto trans = Transform();
	Camera *camera = new Camera(trans);

	level1->SetActiveCamera(camera);

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
				auto suziObject = new DrawableObject(new Transform(
					Location(),
					Rotation(),
					Scale(0.2f)
				));
				auto suziModel = new Model(suziSmooth, sizeof(suziSmooth) / (sizeof(float) * 6));
				suziObject->SetModel(suziModel);
				level2->AddObject(suziObject);

				auto suziObject2 = new DrawableObject(new Transform(
					Location(.5f, 0.0f, 0.0f),
					Rotation(),
					Scale(0.7f)
				));
				auto suziModel2 = new Model(gift, sizeof(gift) / (sizeof(float) * 6));
				suziObject2->SetModel(suziModel2);
				level2->AddObject(suziObject2);

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
