//
// Created by Petr Pavlík on 07.10.2025.
//

#include "CameraComponent.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Application.h"
#include "Core/Events/InputManager.h"


glm::mat4 CameraComponent::GetCameraViewMatrix()
{
    return glm::lookAt(GetWorldTransform().GetLocation().AsVec3(),
                       GetWorldTransform().GetLocation().AsVec3() + _lookTargetLocation.AsVec3(),
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 CameraComponent::GetCameraProjectionMatrix()
{
    float aspectRatio = Application::GetInstance()->GetWindow()->GetAspectRatio();

    return glm::perspective(glm::radians(GetFOV()), aspectRatio, 0.1f, 100.0f);
}

void CameraComponent::SetSensitivity(float sensitivity)
{
    _sensitivity = sensitivity;
}

float CameraComponent::GetSensitivity()
{
    return _sensitivity;
}

float CameraComponent::GetFOV()
{
    return _fov;
}

void CameraComponent::SetFOV(float fov)
{
    _fov = fov;
}

void CameraComponent::SetLookTargetLocation(const Location &target)
{
    _lookTargetLocation = target;
}

Location CameraComponent::GetLookTargetLocation()
{
    return _lookTargetLocation;
}

void CameraComponent::OnTick()
{
    GameObjectComponent::OnTick();

    auto camerRot = GetWorldRotation();

    float yaw = camerRot.GetYaw(),
            pitch = camerRot.GetPitch();

    if (InputManager::IsMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        auto controller = GetParent()->GetController();

        float xOffset = controller->GetMousePosition().x - controller->GetLastMousePosition().x;
        float yOffset = controller->GetLastMousePosition().y - controller->GetMousePosition().y;

        xOffset *= _sensitivity;
        yOffset *= _sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 front = GetLookTargetLocation().AsVec3();
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(front);

        SetLookTargetLocation(Location(
            front.x,
            front.y,
            front.z
        ));

        // TODO: Apply the yaw to the player character
        SetLocalRotation(Rotation(0, pitch, yaw));
    }
}
