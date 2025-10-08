//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Level.h"

void Level::AddObject(GameObject *gameObject)
{
    _gameObjects.push_back(gameObject);
}

void Level::RemoveObject(GameObject *gameObject) {}

void Level::SpawnGameObject(GameObject *gameObject)
{
    this->AddObject(gameObject);
}

void Level::SpawnGameObject(GameObject *gameObject, const Transform transform)
{
    gameObject->SetWorldTransform(transform);
    this->AddObject(gameObject);
}

// Camera
void Level::SetActiveCamera(CameraComponent *camera)
{
    _activeCamera = camera;
    _activeCamera->OnActivated();
}

CameraComponent *Level::GetActiveCamera()
{
    return _activeCamera;
}

void Level::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}
void Level::OnMouseKeyEvent(MouseKeyEventArgs e) {}
void Level::OnLoaded() {}
void Level::OnUnloaded() {}
void Level::OnRendered() {}

void Level::OnTick()
{
    for (auto go: _gameObjects)
    {
        go->OnTick();
    }
}
