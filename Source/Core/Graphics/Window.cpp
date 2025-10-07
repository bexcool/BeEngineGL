//
// Created by Petr Pavlík on 06.10.2025.
//

#include "Window.h"

#include <GL/glew.h>

static void error_callback(int error, const char *description) { fputs(description, stderr); }

Window::Window(int width, int height, std::string title)
{
    _width = width;
    _height = height;

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
    _glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!_glfwWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_glfwWindow);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(this->_glfwWindow, &width, &height);
    float ratio = width / (float) height;
    glViewport(0, 0, width, height);
}

GLFWwindow *Window::AsGLFWWindow()
{
    return _glfwWindow;
}

int Window::GetWidth()
{
    return _width;
}

int Window::GetHeight()
{
    return _height;
}

float Window::GetAspectRatio()
{
    return static_cast<float>(_width) / static_cast<float>(_height);
}
