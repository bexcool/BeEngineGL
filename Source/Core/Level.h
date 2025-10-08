//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include "ObjectComponents/CameraComponent.h"
#include "Events/KeyboardKeyEventArgs.h"
#include "Events/MouseKeyEventArgs.h"


class Level
{
    CameraComponent *_activeCamera;
    std::string _name;

    std::vector<GameObject *> _gameObjects;

public:
    Level(std::string name) : _name(name) {};

    std::string GetName() { return _name; }

    void AddObject(GameObject *gameObject);
    void RemoveObject(GameObject *gameObject);

    void SpawnGameObject(GameObject *gameObject);
    void SpawnGameObject(GameObject *gameObject, const Transform transform);

    std::vector<GameObject *> *GetGameObjects() { return &_gameObjects; }

    // Camera
    void SetActiveCamera(CameraComponent *camera);
    CameraComponent *GetActiveCamera();

    /**
     * Called when level was loaded.
     */
    virtual void OnLoaded();

    /**
     * Called when level was unloaded.
     */
    virtual void OnUnloaded();

    /**
     * Called everytime renderer request a draw.
     */
    virtual void OnRendered();

    /**
     * Called every loop iteration before rendering.
     */
    virtual void OnTick();

    /**
     * Called when a key press occured.
     * @param e Key event arguments.
     */
    virtual void OnKeyboardKeyEvent(KeyboardKeyEventArgs e);

    /**
     * Called when a key press occured.
     * @param e Key event arguments.
     */
    virtual void OnMouseKeyEvent(MouseKeyEventArgs e);
};
