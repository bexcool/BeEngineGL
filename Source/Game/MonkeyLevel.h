//
// Created by Petr Pavlík on 09.10.2025.
//

#pragma once
#include "BECore/Level.h"


class MonkeyLevel : public Level
{
public:
    MonkeyLevel() : Level("MonkeyLevel") {};
    virtual ~MonkeyLevel() = default;
    void OnLoaded() override;
    void OnUnloaded() override;
    void OnRendered() override;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
