//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerController.h"

#include <algorithm>
#include <typeinfo>

#include "BECore/Application.h"
#include "BECore/Events/InputManager.h"
#include "BECore/ObjectComponents/CharacterCollisionComponent.h"
#include "BECore/ObjectComponents/ModelComponent.h"
#include "BECore/Objects/Character/Character.h"
#include "BECore/logger.h"
#include "EngineResources/Assets/Materials/MAT_Red.h"

void PlayerController::SetRun(bool isRunning)
{
    _isRunnig = isRunning;
}

void PlayerController::SetFlying(bool flying)
{
    _isFlying = flying;
    if (_isFlying)
    {
        _velocity = Vector3(0, 0, 0);
        _onGround = false;
    }

    if (auto *character = dynamic_cast<Character *>(GetOwner()))
        if (auto *charComp = character->GetCharacterCollision())
            charComp->SetFlying(_isFlying);
}

void PlayerController::MovePlayer()
{
    auto *app = Application::GetInstance();
    float deltaTime = app->GetDeltaTime();
    auto front = static_cast<Vector3>(app->GetLevel()->GetActiveCamera()->GetLookTargetLocation());

    CharacterCollisionComponent *charComp = nullptr;
    if (auto *character = dynamic_cast<Character *>(GetOwner()))
        charComp = character->GetCharacterCollision();

    if (auto *character = dynamic_cast<Character *>(GetOwner()))
    {
        float speed = _isRunnig ? character->GetRunSpeed() : character->GetWalkSpeed();
        glm::vec3 right = glm::normalize(glm::cross(front.AsVec3(), glm::vec3(0.0f, 1.0f, 0.0f)));

        glm::vec3 inputDir(0.0f);
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W)) inputDir += front.AsVec3();
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S)) inputDir -= front.AsVec3();
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A)) inputDir -= right;
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D)) inputDir += right;
        inputDir.y = 0.0f;

        float inputLen = glm::length(inputDir);
        if (inputLen > 0.001f) inputDir = glm::normalize(inputDir);

        if (_isFlying)
        {
            glm::vec3 velocity = inputDir * speed;
            if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE))
                velocity.y = speed;
            if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER))
                velocity.y = -speed;

            if (charComp)
            {
                charComp->SetLinearVelocity(velocity);
            }
            else
            {
                GetOwner()->AddWorldLocation(Location(velocity * deltaTime));
            }
        }
        else
        {
            if (charComp)
            {
                glm::vec3 velocity;
                velocity.x = inputDir.x * speed;
                velocity.z = inputDir.z * speed;

                _onGround = charComp->IsOnGround();

                // Request jump: a positive Y is passed so CharacterCollisionComponent
                // picks it up as an impulse on the next UpdateCharacter call.
                velocity.y = 0.0f;
                if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE) && _onGround)
                {
                    velocity.y = _jumpStrength;
                    _onGround = false;
                }

                charComp->SetLinearVelocity(velocity);
            }
            else
            {
                // Fallback movement without physics.
                auto ownerLocation = GetOwner()->GetWorldLocation();
                glm::vec3 velocity = _velocity.AsVec3();
                velocity.x = inputDir.x * speed;
                velocity.z = inputDir.z * speed;
                velocity.y += _gravity * deltaTime;

                if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE) && _onGround)
                {
                    velocity.y = _jumpStrength;
                    _onGround = false;
                }

                ownerLocation += Location(velocity * deltaTime);

                if (ownerLocation.GetY() <= _groundY)
                {
                    ownerLocation.SetY(_groundY);
                    velocity.y = 0.0f;
                    _onGround = true;
                }

                _velocity = Vector3(velocity);
                GetOwner()->SetWorldLocation(ownerLocation);
            }
        }
    }
}

void PlayerController::OnTick()
{
    Controller::OnTick();
    MovePlayer();
}

void PlayerController::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Controller::OnKeyboardKeyEvent(e);

    switch (e.Key)
    {
        case GLFW_KEY_LEFT_SHIFT:
        {
            SetRun(e.Action == GLFW_PRESS);
            break;
        }

        case GLFW_KEY_T:
        {
            if (e.Action == GLFW_RELEASE)
            {
                int index;
                Location location;

                auto go = TraceForStencilObject(&location, &index);

                if (go)
                {
                    for (auto comp: go->GetComponents())
                    {
                        if (auto modelComp = dynamic_cast<ModelComponent *>(comp))
                        {
                            auto model = modelComp->GetModel();
                            _selectedModelPath = model.GetModelPath();
                            _selectedMaterial = model.GetMaterial();
                        }
                    }
                }
            }
            break;
        }

        case GLFW_KEY_F2:
        {
            if (e.Action == GLFW_RELEASE)
                SetFlying(!_isFlying);
            break;
        }

        default:
            break;
    }
}

GameObject *PlayerController::TraceForStencilObject(Location *location, int *stencilIndex)
{
    auto *window = Application::GetInstance()->GetWindow();

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    double mx, my;
    glfwGetCursorPos(window->AsGLFWWindow(), &mx, &my);

    int fbw, fbh;
    glfwGetFramebufferSize(window->AsGLFWWindow(), &fbw, &fbh);

    mx *= (double) fbw / window->GetWidth();
    my *= (double) fbh / window->GetHeight();
    my = fbh - my;

    GLint xFinal = (GLint) mx;
    GLint yFinal = (GLint) my;

    glReadPixels(xFinal, yFinal, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(xFinal, yFinal, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(xFinal, yFinal, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    *stencilIndex = index;

    auto *camera = Application::GetInstance()->GetLevel()->GetActiveCamera();
    glm::vec3 screenX = glm::vec3(xFinal, yFinal, depth);
    glm::mat4 view = camera->GetCameraViewMatrix();
    glm::mat4 projection = camera->GetCameraProjectionMatrix();
    glm::vec4 viewPort = glm::vec4(0, 0, fbw, fbh);

    glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
    LOG_W("Clicked location: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);
    *location = Location(pos.x, pos.y, pos.z);

    for (auto go: *Application::GetInstance()->GetLevel()->GetGameObjects())
    {
        if (go->StencilIndex == index)
            return go;
    }

    return nullptr;
}

void PlayerController::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Controller::OnMouseKeyEvent(e);

    if (e.Button == GLFW_MOUSE_BUTTON_LEFT && e.Action == GLFW_RELEASE)
    {
        if (_selectedModelPath.empty()) return;

        int index;
        Location location;
        TraceForStencilObject(&location, &index);

        auto model = Model();
        model.SetModel(_selectedModelPath, std::make_shared<Material>(*_selectedMaterial));

        auto *go = new GameObject();
        go->AddComponent(new ModelComponent(model));
        Application::GetInstance()->GetLevel()->SpawnGameObject(go, location);
    }
}
