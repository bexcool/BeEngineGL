//
// Created by Petr Pavlík on 22.09.2025.
//

#pragma once

#include "BeEngineGLExport.h"
#include "GameLoop.h"
#include "Graphics/Renderer.h"
#include "Graphics/Window.h"
#include "Level.h"
#include "Physics/PhysicsEngine.h"

struct CursorState
{
    bool visible;
    bool locked;
};

class BE_API Application : public ICoreEvents, IKeyEvents
{
    static Application *_currentApp;

    int _width, _height;
    Window *_window;
    std::string _title;

    Renderer *_renderer;
    GameLoop *_gameLoop;
    PhysicsEngine *_physicsEngine;

    Level *_currentLevel;
    Level *_requestedLevel;

    bool _isCursorVisible = true;
    bool _isCursorLocked = false;

public:
    Application(int width, int height, std::string title);
    static Application *GetInstance() { return _currentApp; }

    void Run(Level *initialLevel);

    void SetCursorState(bool isVisible, bool isLocked);
    void SetCursorState(const CursorState &state);
    CursorState GetCursorState();

    void LoadLevel(Level *level);
    Level *GetLevel() { return _currentLevel; }
    Window *GetWindow() { return _window; }

    float GetDeltaTime();
    float GetTime();

    void OnKeyboardKeyEvent(KeyboardKeyEventArgs e) override;
    void OnMouseKeyEvent(MouseKeyEventArgs e) override;
    void OnRender() override;
    void OnTick() override;
};
