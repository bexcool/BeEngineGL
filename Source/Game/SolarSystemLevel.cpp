//
// Created by Petr Pavlík on 24.11.2025.
//

#include "SolarSystemLevel.h"

#include "Core/Application.h"
#include "Core/logger.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Resources/Assets/Materials/MAT_Red.h"
#include "Resources/Assets/Models/MOD_Sphere.h"

void SolarSystemLevel::OnLoaded()
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

    SetSkyLightIntensity(100);

    auto goSun = new GameObject();
    goSun->AddComponent(new ModelComponent(MOD_Sphere(std::make_shared<MAT_Red>())));
    this->SpawnGameObject(goSun);

    goEarth = new GameObject();
    goEarth->AddComponent(new ModelComponent(MOD_Sphere(), Transform(Location(10, 0, 0))));
    this->SpawnGameObject(goEarth);

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player, Transform(Location(-8, 0, 0), Rotation(), Scale()));

    this->SetActiveCamera(camera);
}

void SolarSystemLevel::OnTick()
{
    Level::OnTick();

    auto rot = goEarth->GetWorldRotation();
    goEarth->SetWorldRotation(Rotation(0, rot.GetYaw() + 100 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", goEarth->GetWorldRotation().GetYaw());
}
