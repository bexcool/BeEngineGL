//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "../Objects/GameObject.h"
#include "../Math/Transform.h"


class CameraComponent : public GameObjectComponent
{
    Location _lookTargetLocation = Location(1, 0, 0);
    float _sensitivity = 0.1f;
    float _fov = 90.0f;

public:
    CameraComponent() : GameObjectComponent() {}

    glm::mat4 GetCameraViewMatrix();
    glm::mat4 GetCameraProjectionMatrix();

    void SetSensitivity(float sensitivity);
    float GetSensitivity();

    float GetFOV();
    void SetFOV(float fov);

    void SetLookTargetLocation(const Location &target);
    Location GetLookTargetLocation();

    void OnTick() override;

    virtual void OnActivated() {};
};
