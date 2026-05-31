//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../Events/KeyboardKeyEventArgs.h"
#include "../Events/MouseKeyEventArgs.h"


class IKeyEvents
{
public:
    virtual ~IKeyEvents() = default;
    virtual void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) = 0;
    virtual void OnMouseKeyEvent(MouseKeyEventArgs e) = 0;
};
