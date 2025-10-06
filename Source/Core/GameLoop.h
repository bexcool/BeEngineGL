//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "Graphics/Renderer.h"


class GameLoop
{
private:
    Renderer *_renderer;

public:
    GameLoop(Renderer *renderer);

    void Start();
};
