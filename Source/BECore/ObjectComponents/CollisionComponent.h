//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once

#include "GameObjectComponent.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

#include <vector>
#include <string>

enum class CollisionMotionType
{
    Static,
    Kinematic,
    Dynamic
};

class CollisionComponent : public GameObjectComponent
{
protected:
    JPH::BodyID _bodyID;
    CollisionMotionType _motionType;
    bool _isTrigger;
    float _mass;

public:
    static std::vector<CollisionComponent *> AllCollisionComponents;

    CollisionComponent(std::string name, CollisionMotionType motionType, bool isTrigger, float mass);
    ~CollisionComponent() override;

    CollisionMotionType GetMotionType() const { return _motionType; }
    bool IsTrigger() const { return _isTrigger; }
    JPH::BodyID GetBodyID() const { return _bodyID; }

    // Subclasses return the shape to create the body with.
    virtual JPH::ShapeRefC CreateShape() = 0;

    void OnAttached(GameObject *parent) override;
    void OnRemovedFromParent() override;
    void OnTick() override;

    // Creates Jolt bodies for components that were attached before their parent had a world position.
    static void CreatePending();

    // Pushes kinematic bodies toward their parent's world transform (called from PhysicsEngine::Step).
    static void SyncKinematic(float deltaTime);

    // Reads dynamic body transforms from Jolt and applies them to parent game objects (called from PhysicsEngine::Step).
    static void SyncDynamic();
};
