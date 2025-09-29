//
// Created by Petr Pavlík on 29.09.2025.
//

#include "Transform.h"

#include <string>

Transform::Transform() {}

Transform::Transform(glm::mat4 *transformMatrix)
{
    this->transformMatrix = transformMatrix;
}
