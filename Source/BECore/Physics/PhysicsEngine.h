//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once

#include "BECore/BeEngineGLExport.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

#include "BECore/Math/Vector3.h"
#include "BECore/Objects/GameObject.h"

struct BE_API HitResult
{
    bool blockingHit = false;
    Vector3 location = Vector3();
    float fraction = 0.0f;
    JPH::BodyID bodyID;
    GameObject *hitObject = nullptr;
    GameObjectComponent *hitComponent = nullptr;
};

namespace PhysicsLayers
{
    static constexpr JPH::ObjectLayer NON_MOVING = 0;
    static constexpr JPH::ObjectLayer MOVING = 1;
    static constexpr JPH::uint NUM_LAYERS = 2;
}

namespace BPLayers
{
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr JPH::uint NUM_LAYERS = 2;
}

class BE_API PhysicsEngine
{
    static PhysicsEngine *_instance;

    JPH::TempAllocatorImpl *_tempAllocator = nullptr;
    JPH::JobSystemThreadPool *_jobSystem = nullptr;
    JPH::PhysicsSystem *_physicsSystem = nullptr;

public:
    PhysicsEngine();
    ~PhysicsEngine();

    static PhysicsEngine *GetInstance() { return _instance; }

    void Initialize();

    // Steps characters, simulates rigid bodies, then syncs dynamic bodies back to game objects.
    void Step(float deltaTime);

    JPH::PhysicsSystem *GetPhysicsSystem() { return _physicsSystem; }
    JPH::TempAllocatorImpl *GetTempAllocator() { return _tempAllocator; }
    JPH::BodyInterface &GetBodyInterface();

    HitResult TraceLine(Location start, Vector3 direction, float distance);
};
