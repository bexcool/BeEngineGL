cmake_minimum_required(VERSION 3.30)
project(ZPG)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZPG
        Source/main.cpp
        Source/Core/Application.cpp
        Source/Core/Application.h
        Source/Core/Graphics/Renderer.cpp
        Source/Core/Graphics/Renderer.h
        Source/Core/Graphics/ShaderProgram.cpp
        Source/Core/Graphics/ShaderProgram.h
        Source/Core/Graphics/Shader.cpp
        Source/Core/Graphics/Shader.h
        Source/Resources/Models/bushes.h
        Source/Resources/Models/gift.h
        Source/Resources/Models/plain.h
        Source/Resources/Models/sphere.h
        Source/Resources/Models/suzi_flat.h
        Source/Resources/Models/suzi_smooth.h
        Source/Resources/Models/tree.h
        Source/Core/Graphics/Model.cpp
        Source/Core/Graphics/Model.h
        Source/Core/DrawableObject.cpp
        Source/Core/DrawableObject.h
        Source/Core/Math/Transform.cpp
        Source/Core/Math/Transform.h
        Source/Core/Math/Translation.cpp
        Source/Core/Math/Translation.h
        Source/Core/Math/Rotation.cpp
        Source/Core/Math/Rotation.h
        Source/Core/Math/Scale.cpp
        Source/Core/Math/Scale.h
        Source/Core/Level.cpp
        Source/Core/Level.h)

find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
target_include_directories(ZPG PRIVATE
        /opt/homebrew/include
        ${CMAKE_SOURCE_DIR}/vendor
)
if (APPLE)
    target_link_directories(ZPG PRIVATE /opt/homebrew/lib)
    target_compile_definitions(ZPG PRIVATE GL_SILENCE_DEPRECATION)
    target_link_libraries(ZPG
            glfw
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            "-lGLEW"
    )
endif ()