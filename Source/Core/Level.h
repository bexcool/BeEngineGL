//
// Created by Petr Pavlík on 05.10.2025.
//

#pragma once
#include "Camera.h"
#include "DrawableObject.h"
#include "Events/KeyEventArgs.h"


class Level
{
    Camera *_camera;
    vector<DrawableObject *> _drawableObjects;
    std::string _name;

public:
    Level(std::string name) : _name(name) {};

    std::string GetName() { return _name; }

    void AddObject(DrawableObject *drawableObject);
    void RemoveObject(DrawableObject *drawableObject);

    vector<DrawableObject *> *GetDrawableObjects() { return &_drawableObjects; }

    // Camera
    void SetActiveCamera(Camera *camera);
    Camera *GetActiveCamera();

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
    virtual void OnDraw();

    /**
     * Called every loop iteration before rendering.
     */
    virtual void OnTick();

    /**
     * Called when a key press occured.
     * @param e Key event arguments.
     */
    virtual void OnKeyEvent(KeyEventArgs e);
};
