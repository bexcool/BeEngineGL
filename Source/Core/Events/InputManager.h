//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include <unordered_set>

class InputManager
{
private:
    static std::unordered_set<int> _pressedKeyboardKeys;
    static std::unordered_set<int> _pressedMouseKeys;

public:
    static void Initialize();

    static std::unordered_set<int> *GetPressedKeyboardKeys();
    static std::unordered_set<int> *GetPressedMouseKeys();

    static bool IsKeyboardKeyPressed(int key);
    static bool IsMouseKeyPressed(int key);
};
