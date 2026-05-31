//
// Simple AABB collider component
//
#pragma once

#include <glm/vec3.hpp>
#include <vector>

#include "BECore/Math/Location.h"
#include "GameObjectComponent.h"

class ColliderComponent : public GameObjectComponent
{
    glm::vec3 _halfExtents;
    bool _isTrigger = false;
    bool _isStatic = true;
    bool _isCharacterCollision = false;
    float _mass = 0.0f;
    void *_bodyHandle = nullptr;

public:
    static std::vector<ColliderComponent *> Colliders;

    ColliderComponent(const glm::vec3 &halfExtents = glm::vec3(0.5f, 1.0f, 0.5f), bool isTrigger = false, bool isStatic = true, float mass = 0.0f, bool isCharacterCollision = false);
    ~ColliderComponent();

    void OnAttached(GameObject *parent) override;
    void OnRemovedFromParent() override;

    glm::vec3 GetHalfExtents() const { return _halfExtents; }
    bool IsTrigger() const { return _isTrigger; }
    bool IsStatic() const { return _isStatic; }
    bool IsCharacterCollision() const { return _isCharacterCollision; }
    float GetMass() const { return _mass; }
    void *GetBodyHandle() const { return _bodyHandle; }
    bool HasPhysicsBody() const { return _bodyHandle != nullptr; }

    static void SyncPhysics();
};
