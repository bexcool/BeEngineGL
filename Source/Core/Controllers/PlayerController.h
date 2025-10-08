//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "Controller.h"


class PlayerController : public Controller
{
public:
    void MovePlayer() const;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
