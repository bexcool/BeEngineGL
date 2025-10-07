//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "EventArgs.h"


class KeyboardKeyEventArgs : public EventArgs
{
public:
    int Key, Scancode, Action, Mods;

    KeyboardKeyEventArgs(int key, int scancode, int action, int mods) : Key(key),
                                                                Scancode(scancode),
                                                                Action(action),
                                                                Mods(mods) {}
};
