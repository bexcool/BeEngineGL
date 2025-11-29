//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Rotation.h"

glm::vec3 Rotation::GetForwardVector() const
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(GetPitch())) * cos(glm::radians(GetYaw()));
    forward.y = sin(glm::radians(GetPitch()));
    forward.z = cos(glm::radians(GetPitch())) * sin(glm::radians(GetYaw()));

    return glm::normalize(forward);
}

glm::quat Rotation::AsQuat() const
{
    return glm::quat(glm::vec3(GetRoll(), GetPitch(), GetYaw()));
}

Rotation Rotation::operator+(const Rotation &rotation) const
{
    return {GetRoll() + rotation.GetRoll(), GetPitch() + rotation.GetPitch(), GetYaw() + rotation.GetYaw()};
}
