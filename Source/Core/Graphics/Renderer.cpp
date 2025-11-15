//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Renderer.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <fstream>
#include <iostream>

#include "../ObjectComponents/ModelComponent.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "../Application.h"
#include "Core/logger.h"

using namespace std;

Renderer::Renderer(GLFWwindow *window)
{
	this->_window = window;

	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Renderer::Render() const
{
	auto app = Application::GetInstance();

	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Draw SkyBox
	auto skyBox = app->GetLevel()->GetSkyBox();
	if (skyBox)
	{
		skyBox->Render();
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Draw game objects
	if (app->GetLevel() != nullptr)
	{
		int index = 0;
		for (auto object: (*app->GetLevel()->GetGameObjects()))
		{
			glStencilFunc(GL_ALWAYS, index, 0xFF);
			object->OnRender();
			index++;
		}
	}
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(this->_window);

	app->GetLevel()->OnRendered();
}
