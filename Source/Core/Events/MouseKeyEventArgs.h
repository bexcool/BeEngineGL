//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once


class MouseKeyEventArgs
{
public:
    int Button, Action, Mods;

    MouseKeyEventArgs(int button, int action, int mods) : Button(button), Action(action), Mods(mods) {}
};
