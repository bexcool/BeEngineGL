cmake_minimum_required(VERSION 3.30)
project(ZPG)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZPG
        Source/main.cpp
        Source/Application.cpp
        Source/Application.h
        Source/Graphics/Graphics.cpp
        Source/Graphics/Graphics.h
        Source/Graphics/ShaderProgram.cpp
        Source/Graphics/ShaderProgram.h
        Source/Graphics/Shader.cpp
        Source/Graphics/Shader.h
        Source/Models/bushes.h
        Source/Models/gift.h
        Source/Models/plain.h
        Source/Models/sphere.h
        Source/Models/suzi_flat.h
        Source/Models/suzi_smooth.h
        Source/Models/tree.h)

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