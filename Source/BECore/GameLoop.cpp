//
// Created by Petr Pavlík on 06.10.2025.
//

#include "GameLoop.h"

#include <GL/glew.h>

#include "Application.h"
#include "ObjectComponents/ColliderComponent.h"
#include "logger.h"

GameLoop::GameLoop(Renderer* renderer, PhysicsEngine* physicsEngine) {
    _renderer = renderer;
    _physicsEngine = physicsEngine;
}

void GameLoop::Start() {
    LOG("Starting game loop...");

    auto win = Application::GetInstance()->GetWindow()->AsGLFWWindow();
    glEnable(GL_DEPTH_TEST);

    _lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(win)) {
        double currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrameTime;
        _lastFrameTime = currentFrame;

        // Poll GLFW events
        glfwPollEvents();

        // Sync physics
        _physicsEngine->Step(GetDeltaTime());
        ColliderComponent::SyncPhysics();

        // Call tick on level
        Application::GetInstance()->OnTick();

        // Render level
        _renderer->Render();
    }

    glfwDestroyWindow(win);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

float GameLoop::GetDeltaTime() {
    return _deltaTime;
}
