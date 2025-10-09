//
// Created by Petr Pavlík on 06.10.2025.
//

#include "GameLoop.h"

#include <GL/glew.h>

#include "logger.h"
#include "Application.h"

GameLoop::GameLoop(Renderer *renderer)
{
    _renderer = renderer;
}


void GameLoop::Start()
{
    LOG("Starting game loop...");

    auto win = Application::GetInstance()->GetWindow()->AsGLFWWindow();
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(win))
    {
        double currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrameTime;
        _lastFrameTime = currentFrame;

        // Poll GLFW events
        glfwPollEvents();

        // Call tick on level
        Application::GetInstance()->GetLevel()->OnTick();

        // Render level
        _renderer->Render();
    }

    glfwDestroyWindow(win);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

float GameLoop::GetDeltaTime()
{
    return _deltaTime;
}
