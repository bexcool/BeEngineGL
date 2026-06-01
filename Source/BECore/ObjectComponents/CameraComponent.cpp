//
// Created by Petr Pavlík on 07.10.2025.
//

#include "CameraComponent.h"

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>

#include "BECore/Application.h"
#include "BECore/Events/InputManager.h"
#include "BECore/logger.h"

glm::vec3 ComputeCameraForwardVector(float pitchDegrees, float yawDegrees)
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(pitchDegrees)) * cos(glm::radians(yawDegrees));
    forward.y = sin(glm::radians(pitchDegrees));
    forward.z = cos(glm::radians(pitchDegrees)) * sin(glm::radians(yawDegrees));

    float lengthSquared = glm::dot(forward, forward);
    if (lengthSquared < 1e-6f)
    {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }

    return glm::normalize(forward);
}

glm::mat4 CameraComponent::GetCameraViewMatrix()
{
    glm::vec3 eye = GetWorldTransform().GetLocation().AsVec3();
    glm::vec3 forward = _lookTargetLocation.AsVec3();

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    if (glm::dot(right, right) < 1e-6f)
        right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    return glm::lookAt(eye, eye + forward, up);
}

glm::mat4 CameraComponent::GetCameraProjectionMatrix()
{
    float aspectRatio = Application::GetInstance()->GetWindow()->GetAspectRatio();

    return glm::perspective(glm::radians(GetFOV()), aspectRatio, 0.1f, 1000.0f);
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
    glm::vec3 forward = target.AsVec3();
    if (glm::dot(forward, forward) < 1e-6f)
    {
        forward = glm::vec3(1.0f, 0.0f, 0.0f);
    } else
    {
        forward = glm::normalize(forward);
    }

    _lookTargetLocation = Location(forward);
}

Location CameraComponent::GetLookTargetLocation()
{
    return _lookTargetLocation;
}

void CameraComponent::OnTick()
{
    GameObjectComponent::OnTick();

    if (((InputManager::IsMouseKeyPressed(GLFW_MOUSE_BUTTON_RIGHT) || InputManager::IsMouseKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) && !Application::GetInstance()->GetCursorState().locked)
        || Application::GetInstance()->GetCursorState().locked)
    {
        auto controller = GetParent()->GetController();

        float xOffset = controller->GetMousePosition().x - controller->GetLastMousePosition().x;
        float yOffset = controller->GetLastMousePosition().y - controller->GetMousePosition().y;

        xOffset *= _sensitivity;
        yOffset *= _sensitivity;

        _yaw += xOffset;
        _pitch += yOffset;

        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    GetParent()->SetWorldRotation(Rotation(0.0f, 0.0f, -_yaw));
    SetLocalRotation(Rotation(_pitch, 0.0f, 0.0f));
    _lookTargetLocation = Location(ComputeCameraForwardVector(_pitch, _yaw));
}
