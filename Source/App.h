//
// Created by Petr Pavlík on 07.10.2025.
//

#pragma once
#include "Core/Application.h"

#ifdef _WIN32
#ifdef BEAPI_BUILD_DLL
#define BEAPI declspec(dllexport)

#elif defined(BEAPI_DLL)
#define BEAPI declspec(dllimport)

#else
#define BEAPI

#endif
#else
#define BEAPI attribute((visibility("default")))
#endif

class App : public Application {};
