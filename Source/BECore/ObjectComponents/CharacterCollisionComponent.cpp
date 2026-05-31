//
// Created by Petr Pavlík on 31.05.2026.
//

#include "CharacterCollisionComponent.h"

#include <algorithm>
#include <glm/gtc/quaternion.hpp>

#include "BECore/Physics/PhysicsEngine.h"
#include "BECore/Objects/GameObject.h"
#include "BECore/Math/Location.h"

#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Body/BodyFilter.h>
#include <Jolt/Physics/Collision/ShapeFilter.h>

std::vector<CharacterCollisionComponent *> CharacterCollisionComponent::AllCharacterCollisionComponents;

CharacterCollisionComponent::CharacterCollisionComponent(float halfHeight, float radius)
    : GameObjectComponent("CharacterCollisionComponent"), _capsuleHalfHeight(halfHeight), _capsuleRadius(radius) {}

CharacterCollisionComponent::~CharacterCollisionComponent()
{
    auto it = std::find(AllCharacterCollisionComponents.begin(), AllCharacterCollisionComponents.end(), this);
    if (it != AllCharacterCollisionComponents.end()) AllCharacterCollisionComponents.erase(it);

    delete _character;
    _character = nullptr;
}

void CharacterCollisionComponent::OnAttached(GameObject *parent)
{
    GameObjectComponent::OnAttached(parent);
    AllCharacterCollisionComponents.push_back(this);
    // CharacterVirtual is created in CreatePending() during the first physics step, after the
    // parent has been given its world position by SpawnGameObject.
}

void CharacterCollisionComponent::CreatePending()
{
    auto *pe = PhysicsEngine::GetInstance();
    if (!pe) return;

    for (auto *comp: AllCharacterCollisionComponents)
    {
        if (comp->_character != nullptr) continue;
        auto *parent = comp->GetParent();
        if (!parent) continue;

        float capsuleOffset = comp->_capsuleHalfHeight + comp->_capsuleRadius;
        JPH::CapsuleShapeSettings capsuleSettings(comp->_capsuleHalfHeight, comp->_capsuleRadius);
        JPH::ShapeRefC capsuleShape = capsuleSettings.Create().Get();

        JPH::RotatedTranslatedShapeSettings rtSettings(
            JPH::Vec3(0.0f, capsuleOffset, 0.0f),
            JPH::Quat::sIdentity(),
            capsuleShape
        );
        JPH::ShapeRefC shape = rtSettings.Create().Get();

        auto loc = comp->GetWorldLocation();
        glm::quat glmQuat = comp->GetWorldRotation().AsQuat();
        JPH::RVec3 pos((float) loc.GetX(), (float) loc.GetY(), (float) loc.GetZ());
        JPH::Quat rot(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);

        JPH::CharacterVirtualSettings settings;
        settings.mShape = shape;
        settings.mSupportingVolume = JPH::Plane(JPH::Vec3::sAxisY(), -comp->_capsuleHalfHeight);
        settings.mMaxSlopeAngle = JPH::DegreesToRadians(45.0f);
        settings.mMass = 80.0f;
        settings.mMaxStrength = 100.0f;

        comp->_character = new JPH::CharacterVirtual(&settings, pos, rot, pe->GetPhysicsSystem());
    }
}

void CharacterCollisionComponent::OnRemovedFromParent()
{
    auto it = std::find(AllCharacterCollisionComponents.begin(), AllCharacterCollisionComponents.end(), this);
    if (it != AllCharacterCollisionComponents.end()) AllCharacterCollisionComponents.erase(it);

    delete _character;
    _character = nullptr;
}

void CharacterCollisionComponent::SetLinearVelocity(glm::vec3 velocity)
{
    _desiredVelocity = velocity;
}

void CharacterCollisionComponent::SetFlying(bool flying)
{
    _isFlying = flying;
    if (_isFlying)
        _verticalVelocity = 0.0f;
}

glm::vec3 CharacterCollisionComponent::GetLinearVelocity() const
{
    if (!_character) return {0.0f, 0.0f, 0.0f};
    auto v = _character->GetLinearVelocity();
    return {v.GetX(), _verticalVelocity, v.GetZ()};
}

bool CharacterCollisionComponent::IsOnGround() const
{
    return _character && _character->IsSupported();
}

glm::vec3 CharacterCollisionComponent::GetPosition() const
{
    if (!_character) return {0.0f, 0.0f, 0.0f};
    auto p = _character->GetPosition();
    return {(float) p.GetX(), (float) p.GetY(), (float) p.GetZ()};
}

void CharacterCollisionComponent::UpdateCharacter(float deltaTime)
{
    if (!_character) return;
    
    auto *parent = GetParent();
    if (!parent) return;

    auto *pe = PhysicsEngine::GetInstance();
    if (!pe) return;

    // Build combined velocity: horizontal from desired, vertical from gravity tracking.
    glm::vec3 velocity = _desiredVelocity;

    JPH::Vec3 gravityForExtendedUpdate = pe->GetPhysicsSystem()->GetGravity();

    if (_isFlying)
    {
        // Flying: use desired Y directly, no gravity.
        _verticalVelocity = _desiredVelocity.y;
        gravityForExtendedUpdate = JPH::Vec3::sZero();
    } else if (_character->IsSupported())
    {
        // On ground: use the moving platform's Y velocity and reset our gravity accumulator.
        JPH::Vec3 groundVel = _character->GetGroundVelocity();
        if (_desiredVelocity.y > 0.0f)
        {
            // Jump was requested — apply it and leave ground.
            _verticalVelocity = _desiredVelocity.y;
        } else
        {
            _verticalVelocity = groundVel.GetY();
        }
    } else
    {
        // In air: accumulate gravity.
        _verticalVelocity += pe->GetPhysicsSystem()->GetGravity().GetY() * deltaTime;
    }

    velocity.y = _verticalVelocity;
    _character->SetLinearVelocity(JPH::Vec3(velocity.x, velocity.y, velocity.z));

    // Default filters — allow the character to collide with everything.
    JPH::BroadPhaseLayerFilter bpFilter;
    JPH::ObjectLayerFilter objFilter;
    JPH::BodyFilter bodyFilter;
    JPH::ShapeFilter shapeFilter;

    JPH::CharacterVirtual::ExtendedUpdateSettings extSettings;
    _character->ExtendedUpdate(deltaTime,
                               gravityForExtendedUpdate,
                               extSettings,
                               bpFilter,
                               objFilter,
                               bodyFilter,
                               shapeFilter,
                               *pe->GetTempAllocator());

    // Sync position back to the parent game object.
    auto pos = _character->GetPosition();
    parent->SetWorldLocation(Location((float) pos.GetX(), (float) pos.GetY(), (float) pos.GetZ()));

    // Reset horizontal desired velocity so next frame's input doesn't carry stale momentum.
    _desiredVelocity.x = 0.0f;
    _desiredVelocity.z = 0.0f;
    // Keep _desiredVelocity.y for jump intent; PlayerController will overwrite it each frame.
    _desiredVelocity.y = 0.0f;
}

void CharacterCollisionComponent::UpdateAll(float deltaTime)
{
    for (auto *comp: AllCharacterCollisionComponents)
    {
        comp->UpdateCharacter(deltaTime);
    }
}
