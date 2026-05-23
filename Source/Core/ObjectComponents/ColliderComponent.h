//
// Simple AABB collider component
//
#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "Core/Math/Location.h"
#include "GameObjectComponent.h"

class ColliderComponent : public GameObjectComponent
{
    glm::vec3 _halfExtents;
    bool _isTrigger = false;
    bool _isStatic = true;
    float _mass = 0.0f;

    static std::vector<ColliderComponent *> Colliders;

public:
    ColliderComponent(const glm::vec3 &halfExtents = glm::vec3(0.5f, 1.0f, 0.5f), bool isTrigger = false, bool isStatic = true, float mass = 0.0f);
    ~ColliderComponent();

    void OnAttached(GameObject *parent) override;
    void OnRemovedFromParent() override;

    glm::vec3 GetHalfExtents() const { return _halfExtents; }
    bool IsTrigger() const { return _isTrigger; }
    bool IsStatic() const { return _isStatic; }
    float GetMass() const { return _mass; }

    // Resolve collisions for this collider given desired world location (centre). Modifies desiredLocation to avoid penetration.
    static void ResolveCollision(ColliderComponent *mover, Location &desiredLocation);
};
