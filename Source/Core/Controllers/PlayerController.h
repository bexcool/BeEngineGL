//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "Controller.h"


class PlayerController : public Controller
{
    bool _isRunnig = false;

public:
    void SetRun(bool isRunning);

    void MovePlayer() const;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
