//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include <glm/detail/func_trigonometric.inl>

#include "Core/Application.h"
#include "Core/Events/InputManager.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Core/Objects/Character/PlayerCharacter.h"
#include "Resources/Models/MOD_Bush.h"
#include "Resources/Models/MOD_Tree.h"
#include "Resources/Models/MOD_SuziFlat.h"

GameObject *goLight1 = new GameObject();
GameObject *goLight2 = new GameObject();

void TestLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);
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
    auto suziObject = new GameObject();

    auto suziModel = new ModelComponent();
    suziModel->SetModel(MOD_SuziFlat(ShaderInfo("./Resources/Shaders/default.frag")));
    suziObject->AddComponent(suziModel);

    this->SpawnGameObject(suziObject, suziTrans);


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

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);

    goLight1->AddComponent(new LightComponent());
    goLight1->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo("./Resources/Shaders/default.frag"))));
    this->SpawnGameObject(goLight1, Transform(Location(30, 3, 20), Rotation(), Scale(0.3)));

    goLight2->AddComponent(new LightComponent());
    goLight2->AddComponent(new ModelComponent(MOD_DefaultSphere(ShaderInfo("./Resources/Shaders/default.frag"))));
    this->SpawnGameObject(goLight2, Transform(Location(10, 3, 10), Rotation(), Scale(0.3)));

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
                                      Location(static_cast<float>(i) * 5 + 10, 0, static_cast<float>(j) * 5 + 10),
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
                                      Location(static_cast<float>(i) * 5 + 12.5, 0, static_cast<float>(j) * 5 + 12.5),
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
