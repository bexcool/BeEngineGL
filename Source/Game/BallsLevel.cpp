//
// Created by Petr Pavlík on 13.10.2025.
//

#include "BallsLevel.h"

#include "Core/ObjectComponents/ModelComponent.h"
#include "Resources/Models/sphere.h"

void BallsLevel::OnLoaded()
{
    Level::OnLoaded();


    auto ball1Model = new ModelComponent();
    ball1Model->SetModel(sphere, sizeof(sphere) / (sizeof(float) * 6),
                         ShaderInfo("Resources/Shaders/phong.frag", GL_FRAGMENT_SHADER));

    auto ball1 = new GameObject();
    ball1->AddComponent(ball1Model);
    SpawnGameObject(ball1, Transform(Location(0, 0, 2), Rotation(), Scale()));

    auto ball2Model = new ModelComponent();
    ball2Model->SetModel(sphere, sizeof(sphere) / (sizeof(float) * 6));

    auto ball2 = new GameObject();
    ball2->AddComponent(ball2Model);
    SpawnGameObject(ball2, Transform(Location(0, 0, -2), Rotation(), Scale()));

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);
}

void BallsLevel::OnUnloaded()
{
    Level::OnUnloaded();
}

void BallsLevel::OnRendered()
{
    Level::OnRendered();
}

void BallsLevel::OnTick()
{
    Level::OnTick();
}

void BallsLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);
}

void BallsLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}
