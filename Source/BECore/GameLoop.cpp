//
// Created by Petr Pavlík on 06.10.2025.
//

#include "GameLoop.h"

#include <GL/glew.h>

#include "Application.h"
#include "Physics/PhysicsEngine.h"
#include "ObjectComponents/CollisionComponent.h"
#include "logger.h"

GameLoop::GameLoop(Renderer *renderer)
{
    _renderer = renderer;
}

void GameLoop::Start()
{
    LOG("Starting game loop...");

    auto win = Application::GetInstance()->GetWindow()->AsGLFWWindow();
    glEnable(GL_DEPTH_TEST);

    _lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        double currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrameTime;
        _lastFrameTime = currentFrame;

        // Poll GLFW events
        glfwPollEvents();

        // Game logic (player input, AI, etc.)
        Application::GetInstance()->OnTick();

        // Physics: sync kinematic bodies, update characters, step simulation, sync dynamic bodies.
        if (auto *pe = PhysicsEngine::GetInstance()) {
            CollisionComponent::SyncKinematic((float)_deltaTime);
            pe->Step((float)_deltaTime);
        }

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
