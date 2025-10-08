//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Level.h"

void Level::AddObject(DrawableObject *drawableObject)
{
    _drawableObjects.push_back(drawableObject);
}

// Camera
void Level::SetActiveCamera(Camera *camera)
{
    _activeCamera = camera;
    _activeCamera->OnActivated();
}

Camera *Level::GetActiveCamera()
{
    return _activeCamera;
}

void Level::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}
void Level::OnMouseKeyEvent(MouseKeyEventArgs e) {}
void Level::OnLoaded() {}
void Level::OnUnloaded() {}
void Level::OnRendered() {}
void Level::OnTick() {}
