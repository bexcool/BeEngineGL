//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

class Graphics
{
private:
    GLFWwindow *_window;

public:
    Graphics(GLFWwindow *window);

    void StartLoop() const;
};
