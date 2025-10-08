//
// Created by Petr Pavlík on 08.10.2025.
//

#pragma once
#include "../Camera.h"
#include "GameObjectComponent.h"
#include "../Objects/GameObject.h"


class CameraComponent : public GameObjectComponent
{
private:
    Camera *_camera;

public:
    CameraComponent();

    void ActivateCamera();

    // Overrides
    void OnAttached(GameObject *parent) override;
};
