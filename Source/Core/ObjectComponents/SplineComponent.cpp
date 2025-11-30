//
// Created by Petr Pavlík on 30.11.2025.
//

#include "SplineComponent.h"

SplineComponent::SplineComponent() : GameObjectComponent("SplineComponent")
{
    A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                  glm::vec4(3.0, -6.0, 3.0, 0),
                  glm::vec4(-3.0, 3.0, 0, 0),
                  glm::vec4(1, 0, 0, 0));
    B = glm::mat4x3(glm::vec3(-1, 0, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, -1, 0),
                    glm::vec3(1, 0, 0));
}

Location SplineComponent::GetLocationFromAlpha(double alpha)
{
    glm::vec4 parameters = glm::vec4(alpha * alpha * alpha, alpha * alpha, alpha, 1.0f);
    glm::vec3 p = parameters * A * glm::transpose(B);

    return {p.x, p.y, p.z};
}
