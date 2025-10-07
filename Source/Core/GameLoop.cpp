//
// Created by Petr Pavlík on 06.10.2025.
//

#include "GameLoop.h"

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
        Application::GetInstance()->GetLevel()->OnTick();

        _renderer->Render();
        // update other events like input handling
        glfwPollEvents();
    }

    glfwDestroyWindow(win);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
