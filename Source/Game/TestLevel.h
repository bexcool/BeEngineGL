//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "../Core/Level.h"

class TestLevel : public Level
{
public:
    TestLevel() : Level("TestLevel") {}
    virtual ~TestLevel() = default;

    void OnLoaded() override;
    void OnUnloaded() override;
    void OnRendered() override;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
