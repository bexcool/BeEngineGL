//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "Core/Interfaces/ICoreEvents.h"
#include "Core/Interfaces/IKeyEvents.h"
#include "Core/Objects/GameObject.h"

class GameObject;

class Controller : public ICoreEvents, IKeyEvents
{
    GameObject *_owner = nullptr;
    glm::vec2 _lastMousePosition = glm::vec2(0.0f);

    void SetOwner(GameObject *owner);

public:
    [[nodiscard]] GameObject *GetOwner() const;

    virtual void OnPossessed(GameObject *owner);

    glm::vec2 GetMousePosition();
    glm::vec2 GetLastMousePosition();

    void OnRender() override;
    void OnTick() override;
    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
};
