//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "Graphics/Renderer.h"


class GameLoop
{
private:
    Renderer *_renderer;

    float _deltaTime = 0.0f;
    float _lastFrameTime = 0.0f;

public:
    GameLoop(Renderer *renderer);

    void Start();

    float GetDeltaTime();
};
