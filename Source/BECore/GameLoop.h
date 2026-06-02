//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "Graphics/Renderer.h"
#include "Physics/PhysicsEngine.h"


class GameLoop
{
    Renderer *_renderer;
    PhysicsEngine *_physicsEngine;

    double _deltaTime = 0.0f;
    double _lastFrameTime = 0.0f;

public:
    GameLoop(Renderer *renderer, PhysicsEngine *physicsEngine);

    void Start();

    float GetDeltaTime();
};
