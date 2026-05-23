#pragma once

#if defined(_WIN32)
#if defined(BE_BUILD_DLL)
#define BE_API __declspec(dllexport)
#elif defined(BE_USE_DLL)
#define BE_API __declspec(dllimport)
#else
#define BE_API
#endif
#elif defined(__clang__) || defined(__GNUC__)
#define BE_API __attribute__((visibility("default")))
#else
#define BE_API
#endif