//
// Created by Petr Pavlík on 31.05.2026.
//

#pragma once

#include "GameObjectComponent.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>

#include <glm/vec3.hpp>
#include <vector>
#include <string>

// Component that gives a game object Jolt CharacterVirtual collision.
// The CharacterVirtual is a capsule that walks, slides on slopes, steps up stairs,
// and can collide with all static and dynamic rigid bodies in the scene.
class CharacterCollisionComponent : public GameObjectComponent
{
    JPH::CharacterVirtual *_character = nullptr;

    float _capsuleHalfHeight;
    float _capsuleRadius;

    // Desired velocity set by external code each frame (e.g. PlayerController)
    glm::vec3 _desiredVelocity = {0.0f, 0.0f, 0.0f};

    // Accumulated vertical velocity (gravity + jumping)
    float _verticalVelocity = 0.0f;

    bool _isFlying = false;

public:
    static std::vector<CharacterCollisionComponent *> AllCharacterCollisionComponents;

    explicit CharacterCollisionComponent(float halfHeight = 0.9f, float radius = 0.3f);

    ~CharacterCollisionComponent() override;

    // Called by the PlayerController each frame to specify movement intent
    // The Y component is used directly (allows jumping); gravity is applied internally
    void SetLinearVelocity(glm::vec3 velocity);

    // Enables/disables flying mode: gravity is suppressed and Y velocity is used directly
    void SetFlying(bool flying);

    // Returns the velocity the CharacterVirtual reported after the last update
    glm::vec3 GetLinearVelocity() const;

    // True when the character is standing on solid ground or a steep slope
    bool IsOnGround() const;

    // Returns the position of the character from Jolt (center of capsule)
    glm::vec3 GetPosition() const;

    void OnAttached(GameObject *parent) override;
    void OnRemovedFromParent() override;

    // Creates CharacterVirtual for components that were attached before their parent had a world position
    static void CreatePending();

    // Updates this character: applies gravity, calls CharacterVirtual::ExtendedUpdate,
    // then syncs the resulting position back to the parent game object
    void UpdateCharacter(float deltaTime);

    // Calls UpdateCharacter on every registered component
    static void UpdateAll(float deltaTime);
};
