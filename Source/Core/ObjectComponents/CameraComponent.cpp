//
// Created by Petr Pavlík on 08.10.2025.
//

#include "CameraComponent.h"

#include "../Application.h"

void CameraComponent::ActivateCamera()
{
    Application *app = Application::GetInstance();

    if (app->GetLevel() != nullptr)
    {
        app->GetLevel()->SetActiveCamera(_camera);
    }
}
