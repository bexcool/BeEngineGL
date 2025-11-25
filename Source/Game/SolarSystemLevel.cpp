//
// Created by Petr Pavlík on 24.11.2025.
//

#include "SolarSystemLevel.h"

#include "Core/ObjectComponents/ModelComponent.h"
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
    goSun->AddComponent(new ModelComponent(MOD_Sphere()));
    this->SpawnGameObject(goSun);

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player, Transform(Location(-8, 0, 0), Rotation(), Scale()));

    this->SetActiveCamera(camera);
}
