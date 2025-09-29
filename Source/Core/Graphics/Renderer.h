//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

class Renderer
{
private:
    GLFWwindow *_window;

public:
    Renderer(GLFWwindow *window);

    void StartLoop() const;
};
