//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "KeyboardKeyEventArgs.h"
#include "MouseKeyEventArgs.h"


class KeyEvents
{
public:
    virtual void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}
    virtual void OnMouseKeyEvent(MouseKeyEventArgs e) {}
};
