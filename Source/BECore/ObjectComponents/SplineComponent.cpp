//
// Created by Petr Pavlík on 30.11.2025.
//

#include "SplineComponent.h"

SplineComponent::SplineComponent() : GameObjectComponent("SplineComponent")
{
    A = glm::mat4x3(glm::vec3(-1.0, 3.0, -3.0),
                    glm::vec3(3.0, -6.0, 3.0),
                    glm::vec3(-3.0, 3.0, 0),
                    glm::vec3(1, 0, 0));
    B = glm::mat4x3(glm::vec3(-1, 0, 0),
                    glm::vec3(0, 1, 0),
                    glm::vec3(0, -1, 0),
                    glm::vec3(1, 0, 0));
}

SplineComponent::SplineComponent(CurvePoint cp1, CurvePoint cp2) : GameObjectComponent("SplineComponent")
{
    A = glm::mat4x3(
        cp1.p1,
        cp1.p2,
        cp1.p3,
        cp1.p4
    );

    B = glm::mat4x3(
        cp2.p1,
        cp2.p2,
        cp2.p3,
        cp2.p4
    );
}

Location SplineComponent::GetLocationFromAlpha(double alpha)
{
    glm::vec4 parameters = glm::vec4(alpha * alpha * alpha, alpha * alpha, alpha, 1.0f);
    glm::vec3 p = parameters * A * glm::transpose(B);

    return {p.x, p.y, p.z};
}
