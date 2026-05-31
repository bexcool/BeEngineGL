//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Renderer
{
private:
    GLFWwindow *_window;

public:
    Renderer(GLFWwindow *window);

    void Render() const;
};
