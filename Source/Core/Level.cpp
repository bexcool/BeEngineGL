//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Level.h"

void Level::RemoveAndDeleteObject(GameObject *gameObject)
{
    RemoveObject(gameObject);
    delete gameObject;
}

void Level::AddObject(GameObject *gameObject)
{
    _gameObjects.push_back(gameObject);
}

void Level::RemoveObject(GameObject *gameObject)
{
    auto go = std::ranges::find(_gameObjects, gameObject);
    if (go != _gameObjects.end())
        _gameObjects.erase(go);
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

void Level::SetPlayerController(PlayerController *controller)
{
    _playerController = controller;
}

PlayerController *Level::GetPlayerController()
{
    return _playerController;
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
    for (auto i = _gameObjects.begin(); i != _gameObjects.end();)
    {
        GameObject *go = *i;

        if (go->GetDestroyRequested())
        {
            delete go;
            i = _gameObjects.erase(i); // erase returns the next valid iterator
        } else
        {
            ++i;
        }
    }
}

void Level::OnRendered() {}

void Level::OnTick()
{
    for (auto i = _gameObjects.begin(); i != _gameObjects.end();)
    {
        GameObject *go = *i;

        if (go->GetDestroyRequested())
        {
            delete go;
            i = _gameObjects.erase(i); // erase returns the next valid iterator
        } else
        {
            go->OnTick();
            ++i;
        }
    }
}
