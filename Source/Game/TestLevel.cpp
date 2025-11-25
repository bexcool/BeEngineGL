//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include "Core/Application.h"
#include "Core/Events/InputManager.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/Objects/Character/PlayerCharacter.h"
#include "Resources/Assets/Models/MOD_F1.h"
#include "Resources/Assets/Models/MOD_login_pav0531.h"
#include "Resources/Assets/Models/MOD_Plane.h"
#include "Resources/Assets/Models/Shrek/MOD_Fiona.h"
#include "Resources/Assets/Models/Shrek/MOD_Shrek.h"
#include "Resources/Assets/Models/Shrek/MOD_Toilet.h"

std::vector<GameObject *> fireflies;
LightComponent *GOC_Flashlight = new LightComponent(Light{.intensity = 1, .radius = 20, .isPointLight = false});

void TestLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);

    if (e.Action == GLFW_PRESS)
    {
        if (e.Key == GLFW_KEY_F)
        {
            auto light = GOC_Flashlight->GetLight();

            light.intensity = light.intensity ? 0 : 1;

            GOC_Flashlight->SetLight(light);
        }
    }
}

void TestLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}

void TestLevel::OnLoaded()
{
    Level::OnLoaded();

    SetSkyBox(new SkyBoxModel(DEFAULT_CUBEMAP));
    SetSkyLightIntensity(5);

    auto suziTrans = Transform(
        Location(10, 10, 0),
        Rotation(),
        Scale(0.5f)
    );
    auto GO_f1 = new GameObject();
    GO_f1->AddComponent(new ModelComponent(MOD_F1()));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 20}), Transform(Location(12, 5, 0)));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 13, .isPointLight = false}), Transform(Location(-10, 5, -10), Rotation(0, -30, 150)));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 20}), Transform(Location(8, 5, 0)));

    this->SpawnGameObject(GO_f1, suziTrans);

    // Login
    auto loginGO = new GameObject();
    loginGO->AddComponent(new ModelComponent(MOD_login_pav0531()));
    this->SpawnGameObject(loginGO, Transform(Location(0, 5, 0), Rotation(180, 0, 0)));

    // Shrek
    auto shrekGO = new GameObject();
    shrekGO->AddComponent(new ModelComponent(MOD_Shrek()));
    this->SpawnGameObject(shrekGO, Transform(Location(-5, 0, -5)));

    // Fiona
    auto fionaGO = new GameObject();
    fionaGO->AddComponent(new ModelComponent(MOD_Fiona()));
    this->SpawnGameObject(fionaGO, Transform(Location(-10, 0, -5)));

    // Toiled
    auto toiletGO = new GameObject();
    toiletGO->AddComponent(new ModelComponent(MOD_Toilet()));
    this->SpawnGameObject(toiletGO, Transform(Location(-7.5, 0, -5)));

    // Default sphere
    /*
    auto defSphereComp = new ModelComponent();
    defSphereComp->SetModel(MOD_DefaultSphere());

    auto defSphereGO = new GameObject();
    defSphereGO->AddComponent(defSphereComp);
    auto trans = Transform(Location(15, 10, 0), Rotation(), Scale());
    this->SpawnGameObject(defSphereGO, trans);
*/

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    player->AddComponent(GOC_Flashlight, Transform(Rotation(0, 0, 90)));

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);

    /*
    auto goLight1 = new GameObject();
    goLight1->AddComponent(new LightComponent(Light{.intensity = 0.2, .radius = 3}));
    goLight1->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo{
        .fragmentShaderPath = "./Resources/Shaders/default.frag"
    })));
    this->SpawnGameObject(goLight1, Transform(Location(30, 5, 20), Rotation(), Scale(0.1)));
    fireflies.push_back(goLight1);

    auto goLight2 = new GameObject();
    goLight2->AddComponent(new LightComponent(Light{.intensity = 0.2, .radius = 3}));
    goLight2->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo{
        .fragmentShaderPath = "./Resources/Shaders/default.frag"
    })));
    this->SpawnGameObject(goLight2, Transform(Location(35, 5, 23), Rotation(), Scale(0.1)));
    fireflies.push_back(goLight2);

    auto goLight3 = new GameObject();
    goLight3->AddComponent(new LightComponent(Light{.intensity = 0.2, .radius = 3}));
    goLight3->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo{
        .fragmentShaderPath = "./Resources/Shaders/default.frag"
    })));
    this->SpawnGameObject(goLight3, Transform(Location(35, 5, 18), Rotation(), Scale(0.1)));
    fireflies.push_back(goLight3);
    */
    auto planeGO = new GameObject();
    planeGO->AddComponent(new ModelComponent(MOD_Plane()));
    this->SpawnGameObject(planeGO, Transform(Location(), Rotation(), Scale(100)));
    /*
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto treeGO = new GameObject();
            treeGO->SetName("treeGO");

            auto treeModelComp = new ModelComponent();
            treeModelComp->SetModel(MOD_Tree());
            treeGO->AddComponent(treeModelComp);

            this->SpawnGameObject(treeGO, Transform(
                                      Location(static_cast<float>(i) * 5, 0, static_cast<float>(j) * 5),
                                      Rotation(),
                                      Scale()
                                  ));
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto bushModelComp = new ModelComponent();
            bushModelComp->SetModel(MOD_Bush());

            auto bushGO = new GameObject();
            bushGO->AddComponent(bushModelComp);

            this->SpawnGameObject(bushGO, Transform(
                                      Location(static_cast<float>(i) * 5 + 2.5, 0, static_cast<float>(j) * 5 + 2.5),
                                      Rotation(),
                                      Scale()
                                  ));
        }
    }
    */
}


void TestLevel::OnUnloaded()
{
    Level::OnUnloaded();
}

void TestLevel::OnRendered()
{
    Level::OnRendered();
}

void TestLevel::OnTick()
{
    Level::OnTick();

    float moveAmountX = sin(glfwGetTime() + 1452) / 30;
    float moveAmountY = sin(glfwGetTime() + 5353) / 50;
    float moveAmountZ = sin(glfwGetTime()) / 30;
    //LOG_W("Move amount: %f", moveAmount);
    for (int i = 0; i < fireflies.size(); i++)
    {
        bool invertZ = i % 2 == 0;

        fireflies[i]->AddWorldLocation(Location(moveAmountX, moveAmountY, moveAmountZ * (invertZ ? -1 : 1)));
    }
}
