//
// Created by Petr Pavlík on 13.10.2025.
//

#include "BallsLevel.h"

#include "Core/Application.h"
#include "Core/logger.h"
#include "Core/ObjectComponents/ModelComponent.h"

GameObject *ballPhong = new GameObject();

void BallsLevel::OnLoaded()
{
    Level::OnLoaded();

    SetSkyBox(new SkyBoxModel({
        "./Resources/Assets/Textures/MilkyWay/stars_rt.png",
        "./Resources/Assets/Textures/MilkyWay/stars_lf.png",
        "./Resources/Assets/Textures/MilkyWay/stars_up.png",
        "./Resources/Assets/Textures/MilkyWay/stars_dn.png",
        "./Resources/Assets/Textures/MilkyWay/stars_ft.png",
        "./Resources/Assets/Textures/MilkyWay/stars_bk.png"
    }));

    // Default
    auto ballDefaultModel = new ModelComponent();
    ballDefaultModel->SetModel(MOD_Sphere(std::make_shared<Material>(((ShaderInfo{.fragmentShaderPath = "Resources/Shaders/default.frag"})))));

    auto ballDefault = new GameObject();
    ballDefault->AddComponent(ballDefaultModel);
    //ballDefault->AddComponent(new LightComponent());
    SpawnGameObject(ballDefault, Transform(Location(0, 2, 0), Rotation(), Scale()));

    // Blinn-Phong
    auto ballBlinnPhongModel = new ModelComponent();
    /*
    ballBlinnPhongModel->SetModel(MOD_Sphere(Material(ShaderInfo{
        .fragmentShaderPath = "Resources/Shaders/blinn_phong.frag"
    })));
    */

    auto ballBlinnPhong = new GameObject();
    ballBlinnPhong->AddComponent(ballBlinnPhongModel);
    SpawnGameObject(ballBlinnPhong, Transform(Location(0, -2, 0), Rotation(), Scale()));

    // Phong
    auto ballPhongModel = new ModelComponent();
    //ballPhongModel->SetModel(MOD_Sphere(Material(ShaderInfo{.fragmentShaderPath = "./Resources/Shaders/phong.frag"})));

    ballPhong->AddComponent(ballPhongModel);
    SpawnGameObject(ballPhong, Transform(Location(0, 0, 2), Rotation(), Scale()));

    auto ball2Model = new ModelComponent();
    /*
    ball2Model->SetModel(MOD_Sphere(Material(ShaderInfo{
        .fragmentShaderPath = "./Resources/Shaders/lambert.frag"
    })));
    */

    auto ball2 = new GameObject();
    ball2->AddComponent(ball2Model);
    //ball2->AddComponent(new LightComponent());
    SpawnGameObject(ball2, Transform(Location(0, 0, -2), Rotation(), Scale()));

    auto light = new GameObject();
    light->AddComponent(new LightComponent());
    SpawnGameObject(light);

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player, Transform(Location(-8, 0, 0), Rotation(), Scale()));

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

    float moveAmount = sin(glfwGetTime()) / 40;
    //LOG_W("Move amount: %f", moveAmount);
    //ballPhong->AddWorldLocation(Location(0, moveAmount, 0));
}

void BallsLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);
}

void BallsLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}
