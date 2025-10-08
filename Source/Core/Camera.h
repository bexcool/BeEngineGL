//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "Objects/GameObject.h"
#include "Math/Transform.h"


class Camera : public GameObject
{
    Location _lookTargetLocation = Location(1, 0, 0);

public:
    Camera(Transform &transform);

    glm::mat4 GetCameraViewMatrix();
    glm::mat4 GetCameraProjectionMatrix();

    void SetLookTargetLocation(const Location &target);
    Location GetLookTargetLocation();

    virtual void OnActivated() {};
};
