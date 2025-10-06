//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class Window
{
    GLFWwindow *_glfwWindow;

public:
    Window(int width, int height, std::string title);

    GLFWwindow *AsGLFWWindow();
};
