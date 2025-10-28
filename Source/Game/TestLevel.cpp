//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include "Core/Application.h"
#include "Core/Events/InputManager.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/Objects/Character/PlayerCharacter.h"
#include "Resources/Assets/Models/MOD_F1.h"
#include "Resources/Models/MOD_Bush.h"
#include "Resources/Models/MOD_Plane.h"
#include "Resources/Models/MOD_Tree.h"
#include "Resources/Models/MOD_SuziFlat.h"

GameObject *goLight1 = new GameObject();
GameObject *goLight2 = new GameObject();
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
    auto suziTrans = Transform(
        Location(10, 10, 0),
        Rotation(),
        Scale(0.5f)
    );
    auto GO_f1 = new GameObject();
    GO_f1->AddComponent(new ModelComponent(MOD_F1()));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 20}), Transform(Location(12, 5, 0)));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 30, .isPointLight = false}), Transform(Location(-10, 5, -10), Rotation(0, -30, 150)));
    GO_f1->AddComponent(new LightComponent(Light{.radius = 20}), Transform(Location(8, 5, 0)));

    this->SpawnGameObject(GO_f1, suziTrans);


    // Default sphere
    auto defSphereComp = new ModelComponent();
    defSphereComp->SetModel(MOD_DefaultSphere());

    auto defSphereGO = new GameObject();
    defSphereGO->AddComponent(defSphereComp);
    auto trans = Transform(Location(15, 10, 0), Rotation(), Scale());
    this->SpawnGameObject(defSphereGO, trans);


    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    player->AddComponent(GOC_Flashlight, Transform(Rotation(0, 0, 90)));

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);

    goLight1->AddComponent(new LightComponent());
    goLight1->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo("./Resources/Shaders/default.frag"))));
    this->SpawnGameObject(goLight1, Transform(Location(30, 5, 20), Rotation(), Scale(0.3)));

    auto goLight2Comp = new LightComponent(Light{.isPointLight = false});
    goLight2->AddComponent(goLight2Comp, Transform(Location(), Rotation(0, -90, 0), Scale()));
    auto goLight2Comp2 = new LightComponent(Light{.isPointLight = false});
    goLight2->AddComponent(goLight2Comp2, Transform(Location(), Rotation(0, -45, 0), Scale()));
    goLight2->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo("./Resources/Shaders/default.frag"))));
    this->SpawnGameObject(goLight2, Transform(Location(10, 5, 10), Rotation(), Scale(0.3)));

    auto planeGO = new GameObject();
    planeGO->AddComponent(new ModelComponent(MOD_Plain()));
    this->SpawnGameObject(planeGO, Transform(Location(), Rotation(), Scale(100)));

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
    goLight1->AddWorldLocation(Location(moveAmountX, moveAmountY, moveAmountZ));
    goLight2->AddWorldLocation(Location(-moveAmountX, moveAmountY, -moveAmountZ));
}
