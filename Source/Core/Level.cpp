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
    _camera = camera;
}

Camera *Level::GetActiveCamera()
{
    return _camera;
}

void Level::OnKeyboardKeyEvent(KeyboardKeyEventArgs e) {}
void Level::OnMouseKeyEvent(MouseKeyEventArgs e) {}
void Level::OnLoaded() {}
void Level::OnUnloaded() {}
void Level::OnDraw() {}
void Level::OnTick() {}
