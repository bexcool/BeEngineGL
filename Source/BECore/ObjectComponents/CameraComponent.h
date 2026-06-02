//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/vec3.hpp>

#include "../Math/Transform.h"
#include "../Objects/GameObject.h"

class CameraComponent : public GameObjectComponent
{
    Location _lookTargetLocation = Location(1, 0, 0);
    float _yaw = 0.0f;
    float _pitch = 0.0f;
    float _sensitivity = 0.1f;
    float _fov = 70.0f;

public:
    CameraComponent() : GameObjectComponent("CameraComponent") {}

    glm::mat4 GetCameraViewMatrix();
    glm::mat4 GetCameraProjectionMatrix();

    void SetSensitivity(float sensitivity);
    float GetSensitivity();

    float GetFOV();
    void SetFOV(float fov);

    void SetLookTargetLocation(const Location &target);
    Location GetLookTargetLocation();

    Vector3 GetForwardVector() const override;

    void OnTick() override;

    virtual void OnActivated() {};
};
