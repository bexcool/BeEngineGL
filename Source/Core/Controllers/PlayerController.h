//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "Controller.h"
#include "Core/Graphics/ShaderInfo.h"


class PlayerController : public Controller
{
    bool _isRunnig = false;
    std::string _selectedModelPath;
    ShaderInfo _selectedModelShaderInfo;

public:
    void SetRun(bool isRunning);

    void MovePlayer() const;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    GameObject *TraceForStencilObject(Location *location, int *stencilIndex);
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
