//
// Created by Petr Pavlík on 06.10.2025.
//

#include "TestLevel.h"

#include <glm/detail/func_trigonometric.inl>

#include "Core/Application.h"
#include "Core/Events/InputManager.h"
#include "Core/ObjectComponents/ModelComponent.h"
#include "Resources/Models/suzi_flat.h"
#include "Resources/Models/tree.h"
#include "Resources/Models/bushes.h"
#include "Core/Objects/Character/PlayerCharacter.h"

double lastX = 400, lastY = 300;
float speed = 1;


void TestLevel::OnKeyboardKeyEvent(KeyboardKeyEventArgs e)
{
    Level::OnKeyboardKeyEvent(e);

    if (e.Key == GLFW_KEY_LEFT_SHIFT)
    {
        if (e.Action == GLFW_PRESS) speed = 3;
        else if (e.Action == GLFW_RELEASE) speed = 1;
    }
}

void TestLevel::OnMouseKeyEvent(MouseKeyEventArgs e)
{
    Level::OnMouseKeyEvent(e);
}

void TestLevel::OnLoaded()
{
    auto suziTrans = Transform(
        Location(10, 0, 0),
        Rotation(),
        Scale(0.5f)
    );
    auto suziObject = new GameObject();

    auto suziModel = new ModelComponent();
    suziModel->SetModel(suziFlat, sizeof(suziFlat) / (sizeof(float) * 6));
    suziObject->AddComponent(suziModel);

    this->SpawnGameObject(suziObject, suziTrans);

    auto *player = new PlayerCharacter();
    auto *camera = new CameraComponent();
    player->AddComponent(camera);

    this->SpawnGameObject(player);

    this->SetActiveCamera(camera);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto treeDO = new GameObject();

            auto treeModel = new ModelComponent();
            treeModel->SetModel(tree, sizeof(tree) / (sizeof(float) * 6));
            treeDO->AddComponent(treeModel);

            this->SpawnGameObject(treeDO, Transform(
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
            auto bushDO = new GameObject();

            auto bushModel = new ModelComponent();
            bushModel->SetModel(bushes, sizeof(bushes) / (sizeof(float) * 6));
            bushDO->AddComponent(bushModel);

            this->SpawnGameObject(bushDO, Transform(
                                      Location(static_cast<float>(i) * 5 + 12.5, 0, static_cast<float>(j) * 5 + 12.5),
                                      Rotation(),
                                      Scale()
                                  ));
        }
    }
}

void TestLevel::OnUnloaded() {}
void TestLevel::OnRendered() {}

void TestLevel::OnTick()
{
    Level::OnTick();
}
