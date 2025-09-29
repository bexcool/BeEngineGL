//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include "Core/Graphics/Renderer.h"

class Application
{
private:
	int _width, _height;
	std::string _title;
	GLFWwindow *_window;
	Renderer *_graphics;

	void CreateWindow();

public:
	Application(int width, int height, std::string title);

	GLFWwindow *GetWindow() { return _window; }

	void Run();
};
