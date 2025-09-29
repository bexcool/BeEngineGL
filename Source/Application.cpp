//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Application.h"

#include "Graphics/Graphics.h"

static void error_callback(int error, const char *description) { fputs(description, stderr); }

Application::Application(int width, int height, std::string title)
{
	this->_width = width;
	this->_height = height;
	this->_title = title;
}

void Application::CreateWindow()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	glfwGetFramebufferSize(this->_window, &this->_width, &this->_height);
	float ratio = this->_width / (float) this->_height;
	glViewport(0, 0, this->_width, this->_height);
}

void Application::Run()
{
	CreateWindow();

	_graphics = new Graphics(this->GetWindow());
	_graphics->StartLoop();
}
