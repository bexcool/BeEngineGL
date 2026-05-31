//
// Created by Petr Pavlík on 24.11.2025.
//

#include "SolarSystemLevel.h"

#include "BECore/Application.h"
#include "BECore/logger.h"
#include "BECore/ObjectComponents/ModelComponent.h"
#include "BECore/ObjectComponents/SplineComponent.h"
#include "Resources/Assets/Materials/MAT_Earth.h"
#include "Resources/Assets/Materials/MAT_Mars.h"
#include "Resources/Assets/Materials/MAT_Moon.h"
#include "Resources/Assets/Materials/MAT_Red.h"
#include "Resources/Assets/Materials/MAT_Sun.h"
#include "Resources/Assets/Models/MOD_Sphere.h"
#include "Resources/Assets/Models/Shrek/MAT_Shrek.h"
#include "Resources/Assets/Models/Shrek/MOD_Shrek.h"
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
    goSun->AddComponent(new ModelComponent(MOD_Sphere(std::make_shared<MAT_Sun>()), Transform(Scale(2))));
    goSun->AddComponent(new LightComponent(Light{.intensity = 2, .radius = 50}));
    this->SpawnGameObject(goSun);

    goEarth = new GameObject();
    gocEarth = new ModelComponent(MOD_Sphere(std::make_shared<MAT_Earth>()), Transform(Location(10, 0, 0)));
    goEarth->AddComponent(gocEarth);
    this->SpawnGameObject(goEarth);

    goMoon = new GameObject();
    auto gocMoon = new ModelComponent(MOD_Sphere(std::make_shared<MAT_Moon>()), Transform(Location(2, 0, 0), Scale(0.3)));
    gocMoon->SetRotationLock(true, true, true);
    goMoon->AddComponent(gocMoon);
    this->SpawnGameObject(goMoon);
    goMoon->AttachToGameObject(goEarth, Location(10, 0, 0));

    goUFO = new GameObject();
    goUFO->AddComponent(new ModelComponent(MOD_Shrek(std::make_shared<MAT_Shrek>())), Transform(Location(0, 5, 0)));
    goUFO->AddComponent(new ModelComponent(MOD_Sphere(std::make_shared<MAT_Moon>())), Transform(Location(0, 6.5, 0), Scale(0.3)));
    spline = new SplineComponent();
    goUFO->AddComponent(spline);

    goMars = new GameObject();
    gocMars = new ModelComponent(MOD_Sphere(std::make_shared<MAT_Mars>()), Transform(Location(7, 0, 0), Scale(0.7)));
    gocMars->SetRotationLock(true, true, true);
    goMars->AddComponent(gocMars);
    this->SpawnGameObject(goMars);

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

    auto marsRot = goMars->GetWorldRotation();
    goMars->SetWorldRotation(Rotation(0, marsRot.GetPitch() + 25 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", goMars->GetWorldRotation().GetPitch());

    auto marsModRot = gocMars->GetLocalRotation();
    gocMars->SetLocalRotation(Rotation(0, marsModRot.GetPitch() + 340 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", gocMars->GetLocalRotation().GetPitch());

    auto earthRot = goEarth->GetWorldRotation();
    goEarth->SetWorldRotation(Rotation(0, earthRot.GetPitch() + 50 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", goEarth->GetWorldRotation().GetPitch());

    auto earthModRot = gocEarth->GetLocalRotation();
    gocEarth->SetLocalRotation(Rotation(0, earthModRot.GetPitch() + 360 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", gocEarth->GetLocalRotation().GetPitch());

    auto moonRot = goMoon->GetWorldRotation();
    goMoon->SetWorldRotation(Rotation(0, moonRot.GetPitch() + 10 * Application::GetInstance()->GetDeltaTime(), 0));
    LOG_W("Rotation: %f", goMoon->GetWorldRotation().GetPitch());

    double alpha = sin(glfwGetTime() + 1452);
    Location test = spline->GetLocationFromAlpha(alpha);

    LOG_W("Alpha: %f Location: %f %f %f", alpha, test.GetX(), test.GetY(), test.GetZ());
    goUFO->SetWorldLocation(test);
}
