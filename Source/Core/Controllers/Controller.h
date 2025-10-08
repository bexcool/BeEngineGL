//
// Created by Petr Pavlík on 06.10.2025.
//

#pragma once
#include "../Events/CoreEvents.h"
#include "../Events/KeyEvents.h"
#include "../Objects/GameObject.h"

class GameObject;

class Controller : public CoreEvents, KeyEvents
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
