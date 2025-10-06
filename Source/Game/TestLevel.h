//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "../Core/Level.h"

class TestLevel : public Level
{
public:
    TestLevel(std::string title) : Level(title) {};

    void OnLoaded() override;
    void OnUnloaded() override;
    void OnDraw() override;
    void OnTick() override;
    void OnKeyEvent(KeyEventArgs event) override;
};
