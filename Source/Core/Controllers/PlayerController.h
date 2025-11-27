//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "Controller.h"
#include "Core/Graphics/ShaderInfo.h"
#include "Core/Graphics/Material/Material.h"


class PlayerController : public Controller
{
    bool _isRunnig = false;
    std::string _selectedModelPath;
    std::shared_ptr<Material> _selectedMaterial;

public:
    void SetRun(bool isRunning);

    void MovePlayer() const;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    GameObject *TraceForStencilObject(Location *location, int *stencilIndex);
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
