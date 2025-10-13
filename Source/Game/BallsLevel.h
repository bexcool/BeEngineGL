//
// Created by Petr Pavlík on 13.10.2025.
//

#pragma once
#include "Core/Level.h"


class BallsLevel : public Level
{
public:
    BallsLevel() : Level("BallsLevel") {};
    virtual ~BallsLevel() = default;
    void OnLoaded() override;
    void OnUnloaded() override;
    void OnRendered() override;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
