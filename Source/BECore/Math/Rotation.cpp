//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Rotation.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

glm::vec3 Rotation::GetForwardVector() const
{
    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, glm::radians(GetRoll()), glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(GetPitch()), glm::vec3(0.0f, 0.0f, 1.0f));
    rotation = glm::rotate(rotation, glm::radians(GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 forward = glm::vec3(rotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    float length = glm::length(forward);
    if (length < 1e-6f)
    {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }

    return forward / length;
}

glm::quat Rotation::AsQuat() const
{
    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, glm::radians(GetRoll()), glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(GetPitch()), glm::vec3(0.0f, 0.0f, 1.0f));
    rotation = glm::rotate(rotation, glm::radians(GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

    return glm::quat_cast(rotation);
}

Rotation Rotation::operator+(const Rotation &rotation) const
{
    return {GetRoll() + rotation.GetRoll(), GetPitch() + rotation.GetPitch(), GetYaw() + rotation.GetYaw()};
}

Rotation Rotation::operator-(const Rotation &rotation) const
{
    return {GetRoll() - rotation.GetRoll(), GetPitch() - rotation.GetPitch(), GetYaw() - rotation.GetYaw()};
}
