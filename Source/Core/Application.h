//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <sstream>

#include "GameLoop.h"
#include "Level.h"
#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

class Application
{
	static Application *_currentApp;

	int _width, _height;
	Window *_window;
	std::string _title;

	Renderer *_renderer;
	GameLoop *_gameLoop;
	Level *_currentLevel;

public:
	Application(int width, int height, std::string title);
	static Application *GetInstance() { return _currentApp; }

	void Run();

	void LoadLevel(Level *level);
	Level *GetLevel() { return _currentLevel; }

	Window *GetWindow() { return _window; }

	void OnKeyEvent(KeyEventArgs e);
};
