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
        float currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrameTime;
        _lastFrameTime = currentFrame;

        Application::GetInstance()->GetLevel()->OnTick();

        _renderer->Render();
        // update other events like input handling
        glfwPollEvents();
    }

    glfwDestroyWindow(win);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

float GameLoop::GetDeltaTime()
{
    return _deltaTime;
}
