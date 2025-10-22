//
// Created by Petr Pavlík on 13.10.2025.
//

#include "BallsLevel.h"

#include "Core/ObjectComponents/ModelComponent.h"
#include "Resources/Models/MOD_DefaultSphere.h"

void BallsLevel::OnLoaded()
{
    Level::OnLoaded();


    // Default
    auto ballDefaultModel = new ModelComponent();
    ballDefaultModel->SetModel(MOD_DefaultSphere(ShaderInfo("Resources/Shaders/default.frag")));

    auto ballDefault = new GameObject();
    ballDefault->AddComponent(ballDefaultModel);
    SpawnGameObject(ballDefault, Transform(Location(0, 2, 0), Rotation(), Scale()));

    // Blinn-Phong
    auto ballBlinnPhongModel = new ModelComponent();
    ballBlinnPhongModel->SetModel(MOD_DefaultSphere(ShaderInfo("Resources/Shaders/blinn_phong.frag")));

    auto ballBlinnPhong = new GameObject();
    ballBlinnPhong->AddComponent(ballBlinnPhongModel);
    SpawnGameObject(ballBlinnPhong, Transform(Location(0, -2, 0), Rotation(), Scale()));

    // Phong
    auto ballPhongModel = new ModelComponent();
    ballPhongModel->SetModel(MOD_DefaultSphere(ShaderInfo("Resources/Shaders/phong.frag")));

    auto ballPhong = new GameObject();
    ballPhong->AddComponent(ballPhongModel);
    SpawnGameObject(ballPhong, Transform(Location(0, 0, 2), Rotation(), Scale()));

    auto ball2Model = new ModelComponent();
    ball2Model->SetModel(MOD_DefaultSphere(ShaderInfo("Resources/Shaders/lambert.frag")));

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
