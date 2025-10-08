//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Level.h"

void Level::AddObject(GameObject *gameObject)
{
    _gameObjects.push_back(gameObject);
}

void Level::RemoveObject(GameObject *gameObject)
{
    _gameObjects.erase(std::find(_gameObjects.begin(), _gameObjects.end(), gameObject));
}

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

void Level::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    for (auto go: _gameObjects)
    {
        go->GetController()->OnKeyboardKeyEvent(e);
    }
}

void Level::OnMouseKeyEvent(MouseKeyEventArgs e) {}
void Level::OnLoaded() {}

void Level::OnUnloaded()
{
    for (auto go: _gameObjects)
    {
        go->Destroy();
    }
}

void Level::OnRendered() {}

void Level::OnTick()
{
    for (auto go: _gameObjects)
    {
        go->OnTick();
    }
}
