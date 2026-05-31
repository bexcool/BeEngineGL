#pragma once

#include <glm/vec3.hpp>
#include <memory>

#include "BECore/Math/Location.h"

class PhysicsEngine
{
public:
    enum class BodyKind
    {
        Static,
        Dynamic,
        Kinematic
    };

    PhysicsEngine();
    ~PhysicsEngine();

    void Initialize();
    void Step(float deltaTime) const;
    // Create a box physics body; returns an opaque handle (nullptr if not created)
    void *CreateBoxBody(const glm::vec3 &halfExtents, const Location &worldLocation, BodyKind bodyKind, float mass, bool isCharacterBody = false) const;
    Location GetBodyLocation(void *bodyHandle) const;
    glm::vec3 GetBodyLinearVelocity(void *bodyHandle) const;
    void SetBodyLocation(void *bodyHandle, const Location &worldLocation);
    void SetBodyLinearVelocity(void *bodyHandle, const glm::vec3 &linearVelocity);
    void MoveKinematicBody(void *bodyHandle, const Location &targetLocation, float deltaTime);
    void DestroyBody(void *bodyHandle);

    static PhysicsEngine *GetInstance();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
