//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "Controller.h"
#include "BECore/Graphics/Material/Material.h"
#include "BECore/Graphics/ShaderInfo.h"
#include "BECore/Math/Vector3.h"

class PlayerController : public Controller
{
    std::string _selectedModelPath;
    std::shared_ptr<Material> _selectedMaterial;

    // Physics movement state
    bool _isRunnig = false;
    bool _isFlying = false;

    Vector3 _velocity = Vector3(0, 0, 0);

    bool _onGround = false;

    float _gravity = -9.81f;
    float _jumpStrength = 5.0f;
    float _groundY = 0.0f; // simple flat ground plane
    float _groundFriction = 8.0f;
    float _airControl = 2.0f;

public:
    void SetRun(bool isRunning);

    void MovePlayer();
    void SetFlying(bool flying);
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    GameObject *TraceForStencilObject(Location *location, int *stencilIndex);
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
