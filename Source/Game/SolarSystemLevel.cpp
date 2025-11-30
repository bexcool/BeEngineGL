//
// Created by Petr Pavlík on 24.11.2025.
//

#include "SolarSystemLevel.h"

#include "Core/Application.h"
#include "Core/logger.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/ObjectComponents/SplineComponent.h"
#include "Resources/Assets/Materials/MAT_Earth.h"
#include "Resources/Assets/Materials/MAT_Red.h"
#include "Resources/Assets/Models/MOD_Sphere.h"
#include "Resources/Assets/Models/Shrek/MAT_Shrek.h"
#include "Resources/Assets/Models/Shrek/TEX_Shrek.h"

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

    SetSkyLightIntensity(10);

    auto goSun = new GameObject();
    goSun->AddComponent(new ModelComponent(MOD_Sphere(std::make_shared<MAT_Red>()), Transform(Scale(2))));
    goSun->AddComponent(new LightComponent(Light{.intensity = 4, .radius = 50}));
    this->SpawnGameObject(goSun);

    goEarth = new GameObject();
    auto gocEarth = new ModelComponent(MOD_Sphere(std::make_shared<MAT_Earth>()), Transform(Location(10, 0, 0)));
    gocEarth->SetRotationLock(true, true, true);
    goEarth->AddComponent(gocEarth);
    this->SpawnGameObject(goEarth);

    goUFO = new GameObject();
    goUFO->AddComponent(new ModelComponent(MOD_Sphere(std::make_shared<MAT_Shrek>())), Transform(Location(0, 5, 0)));
    spline = new SplineComponent();
    goUFO->AddComponent(spline);

    this->SpawnGameObject(goUFO);

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
    goEarth->SetWorldRotation(Rotation(0, rot.GetPitch() + 100 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", goEarth->GetWorldRotation().GetPitch());

    double alpha = sin(glfwGetTime() + 1452);
    Location test = spline->GetLocationFromAlpha(alpha);

    LOG_W("Alpha: %f Location: %f %f %f", alpha, test.GetX(), test.GetY(), test.GetZ());
    goUFO->SetWorldLocation(test);
}
