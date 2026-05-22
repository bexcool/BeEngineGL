//
// Created by Petr Pavlík on 08.10.2025.
//

#include "PlayerController.h"

#include <algorithm>
#include <typeinfo>

#include "Core/Application.h"
#include "Core/Events/InputManager.h"
#include "Core/ObjectComponents/ColliderComponent.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/Objects/Character/Character.h"
#include "Core/logger.h"
#include "Resources/Assets/Materials/MAT_Red.h"
#include "Resources/Assets/Models/Shrek/MOD_Fiona.h"

void PlayerController::SetRun(bool isRunning) {
    _isRunnig = isRunning;
}

void PlayerController::SetFlying(bool flying) {
    _isFlying = flying;
    if (_isFlying) {
        _velocity = Vector3(0, 0, 0);
        _onGround = false;
    }
}

void PlayerController::MovePlayer() {
    auto app = Application::GetInstance();
    auto ownerLocation = GetOwner()->GetWorldLocation();
    auto front = static_cast<Vector3>(app->GetLevel()->GetActiveCamera()->GetLookTargetLocation());
    float deltaTime = app->GetDeltaTime();

    if (auto* character = dynamic_cast<Character*>(GetOwner())) {
        float speed = _isRunnig ? character->GetRunSpeed() : character->GetWalkSpeed();
        Vector3 right(glm::normalize(glm::cross(front.AsVec3(), glm::vec3(0.0f, 1.0f, 0.0f))));

        // Build input direction in XZ plane
        glm::vec3 inputDir(0.0f);
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_W)) inputDir += front.AsVec3();
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_S)) inputDir -= front.AsVec3();
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_A)) inputDir -= right.AsVec3();
        if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_D)) inputDir += right.AsVec3();
        inputDir.y = 0.0f;

        float inputLen = glm::length(inputDir);
        if (inputLen > 0.001f) inputDir = glm::normalize(inputDir);

        if (_isFlying) {
            // simple flying: direct positional control
            ownerLocation += Vector3(inputDir) * speed * deltaTime;

            if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE)) {
                ownerLocation.SetY(ownerLocation.GetY() + speed * deltaTime);
            }

            if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_LEFT_SUPER)) {
                ownerLocation.SetY(ownerLocation.GetY() - speed * deltaTime);
            }

            // clear velocity while flying
            _velocity = Vector3(0, 0, 0);
        } else {
            // walking physics
            // horizontal desired velocity
            glm::vec3 desired = inputDir * speed;

            // accelerate velocity towards desired (simple smoothing)
            float accel = _groundFriction * deltaTime;
            glm::vec3 vel = _velocity.AsVec3();
            vel.x += (desired.x - vel.x) * accel;
            vel.z += (desired.z - vel.z) * accel;

            // gravity
            vel.y += _gravity * deltaTime;

            // jump
            if (InputManager::IsKeyboardKeyPressed(GLFW_KEY_SPACE) && _onGround) {
                vel.y = _jumpStrength;
                _onGround = false;
            }

            // apply velocity to position
            ownerLocation += Vector3(vel) * deltaTime;

            // simple ground collision at groundY
            if (ownerLocation.GetY() <= _groundY) {
                ownerLocation.SetY(_groundY);
                vel.y = 0.0f;
                _onGround = true;

                // apply stronger friction when on ground and no input
                if (inputLen < 0.001f) {
                    vel.x *= std::max(0.0f, 1.0f - _groundFriction * deltaTime);
                    vel.z *= std::max(0.0f, 1.0f - _groundFriction * deltaTime);
                }
            }

            _velocity = Vector3(vel);
        }

        // Resolve collisions if player has a collider
        for (auto comp : GetOwner()->GetComponents()) {
            if (auto col = dynamic_cast<ColliderComponent*>(comp)) {
                ColliderComponent::ResolveCollision(col, ownerLocation);
                break;
            }
        }

        GetOwner()->SetWorldLocation(ownerLocation);
    }
}

void PlayerController::OnTick() {
    Controller::OnTick();

    MovePlayer();
}

void PlayerController::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {
    Controller::OnKeyboardKeyEvent(e);

    switch (e.Key) {
        case GLFW_KEY_LEFT_SHIFT: {
            SetRun(e.Action == GLFW_PRESS);

            break;
        }

        case GLFW_KEY_T: {
            if (e.Action == GLFW_RELEASE) {
                int index;
                Location location;

                auto go = TraceForStencilObject(&location, &index);

                if (go) {
                    for (auto comp : go->GetComponents()) {
                        if (auto modelComp = dynamic_cast<ModelComponent*>(comp)) {
                            auto model = modelComp->GetModel();

                            _selectedModelPath = model.GetModelPath();
                            _selectedMaterial = model.GetMaterial();
                        }
                    }
                }
            }
            break;
        }
        case GLFW_KEY_F: {
            if (e.Action == GLFW_RELEASE) {
                SetFlying(!_isFlying);
            }
            break;
        }
        default:
            break;
    }
}

GameObject* PlayerController::TraceForStencilObject(Location* location, int* stencilIndex) {
    auto window = Application::GetInstance()->GetWindow();

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    GLint x = (GLint)GetMousePosition().x;
    GLint y = (GLint)window->GetHeight() - GetMousePosition().y;

    double mx, my;
    glfwGetCursorPos(window->AsGLFWWindow(), &mx, &my);

    int fbw, fbh;
    glfwGetFramebufferSize(window->AsGLFWWindow(), &fbw, &fbh);

    // Scale to framebuffer coordinates
    mx *= (double)fbw / window->GetWidth();
    my *= (double)fbh / window->GetHeight();

    my = fbh - my;

    GLint xFinal = (GLint)mx;
    GLint yFinal = (GLint)my;

    glReadPixels(xFinal, yFinal, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(xFinal, yFinal, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(xFinal, yFinal, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    *stencilIndex = index;

    LOG_W("Clicked pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil %u",
          x, y, color[0], color[1], color[2], color[3], depth, index);

    auto camera = Application::GetInstance()->GetLevel()->GetActiveCamera();

    glm::vec3 screenX = glm::vec3(xFinal, yFinal, depth);
    glm::mat4 view = camera->GetCameraViewMatrix();
    glm::mat4 projection = camera->GetCameraProjectionMatrix();
    glm::vec4 viewPort = glm::vec4(0, 0, fbw, fbh);

    glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

    LOG_W("Clicked location: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);
    *location = Location(pos.x, pos.y, pos.z);

    for (auto go : *Application::GetInstance()->GetLevel()->GetGameObjects()) {
        if (go->StencilIndex == index)
            return go;
    }

    return nullptr;
}

void PlayerController::OnMouseKeyEvent(MouseKeyEventArgs e) {
    Controller::OnMouseKeyEvent(e);

    if (e.Button == GLFW_MOUSE_BUTTON_LEFT && e.Action == GLFW_RELEASE) {
        if (_selectedModelPath.empty()) return;

        int index;
        Location location;

        TraceForStencilObject(&location, &index);

        auto model = Model();
        model.SetModel(_selectedModelPath, std::make_shared<Material>(*_selectedMaterial));

        auto go = new GameObject();
        go->AddComponent(new ModelComponent(model));

        Application::GetInstance()->GetLevel()->SpawnGameObject(go, location);
    }
}
