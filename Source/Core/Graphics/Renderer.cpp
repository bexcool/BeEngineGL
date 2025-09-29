//
// Created by Petr Pavlík on 22.09.2025.
//

#include "Renderer.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <fstream>
#include <iostream>

#include "Shader.h"
#include "ShaderProgram.h"
#include "../../Resources/Models/suzi_flat.h"

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

void Renderer::StartLoop() const
{
	const char *fragment_shader =
			"#version 330 core\n"
			"in vec3 normal;"
			"out vec4 fragColor;"
			"void main () {"
			"     fragColor = vec4 (normal, 1.0);"
			"}";

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof (suziFlat), suziFlat, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));

	auto *verShader = new Shader(GL_VERTEX_SHADER, "../Source/Resources/Shaders/defaultVertexShader.glsl");
	verShader->Compile();

	auto *fraShader = new Shader(GL_FRAGMENT_SHADER, fragment_shader);
	fraShader->Compile();

	auto *shaderProgram = new ShaderProgram(verShader, fraShader);
	shaderProgram->LinkShaders();

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->_window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram->Use();
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, sizeof(suziFlat)); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->_window);
	}

	glfwDestroyWindow(this->_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
