//
// Created by Petr Pavlík on 07.10.2025.
//

#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Application.h"

Camera::Camera(Transform &transform)
{
    SetWorldTransform(transform);
}


glm::mat4 Camera::GetCameraViewMatrix()
{
    return glm::lookAt(GetWorldTransform().GetLocation(),
                       GetWorldTransform().GetLocation() + _lookTargetLocation,
                       Location());
}

glm::mat4 Camera::GetCameraProjectionMatrix()
{
    float aspectRatio = Application::GetInstance()->GetWindow()->GetAspectRatio();

    return glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

void Camera::SetLookTargetLocation(const Location &target)
{
    _lookTargetLocation = target;
}
