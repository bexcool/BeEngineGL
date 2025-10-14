cmake_minimum_required(VERSION 3.30)
project(ZPG)

set(CMAKE_CXX_STANDARD 20)

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
        Source/Resources/Models/ModelDatas/bushes.h
        Source/Resources/Models/ModelDatas/gift.h
        Source/Resources/Models/ModelDatas/plain.h
        Source/Resources/Models/ModelDatas/sphere.h
        Source/Resources/Models/ModelDatas/suzi_flat.h
        Source/Resources/Models/ModelDatas/suzi_smooth.h
        Source/Resources/Models/ModelDatas/tree.h
        Source/Core/ObjectComponents/ModelComponent.cpp
        Source/Core/ObjectComponents/ModelComponent.h
        Source/Core/Math/Transform.cpp
        Source/Core/Math/Transform.h
        Source/Core/Math/Location.cpp
        Source/Core/Math/Location.h
        Source/Core/Math/Rotation.cpp
        Source/Core/Math/Rotation.h
        Source/Core/Math/Scale.cpp
        Source/Core/Math/Scale.h
        Source/Core/Level.cpp
        Source/Core/Level.h
        Source/Core/Graphics/Window.cpp
        Source/Core/Graphics/Window.h
        Source/Core/Controllers/Controller.cpp
        Source/Core/Controllers/Controller.h
        Source/Core/Events/InputManager.cpp
        Source/Core/Events/InputManager.h
        Source/Core/Events/EventArgs.cpp
        Source/Core/Events/EventArgs.h
        Source/Core/Events/KeyboardKeyEventArgs.cpp
        Source/Core/Events/KeyboardKeyEventArgs.h
        Source/Game/TestLevel.cpp
        Source/Game/TestLevel.h
        Source/Core/GameLoop.cpp
        Source/Core/GameLoop.h
        Source/Core/logger.c
        Source/Core/logger.h
        Source/Core/ObjectComponents/CameraComponent.cpp
        Source/Core/ObjectComponents/CameraComponent.h
        Source/Core/Objects/GameObject.cpp
        Source/Core/Objects/GameObject.h
        Source/App.cpp
        Source/App.h
        Source/Core/Events/MouseKeyEventArgs.cpp
        Source/Core/Events/MouseKeyEventArgs.h
        Source/Core/ObjectComponents/GameObjectComponent.cpp
        Source/Core/ObjectComponents/GameObjectComponent.h
        Source/Core/Controllers/PlayerController.cpp
        Source/Core/Controllers/PlayerController.h
        Source/Core/Events/EventDispatcher.cpp
        Source/Core/Events/EventDispatcher.h
        Source/Core/Objects/Character/Character.cpp
        Source/Core/Objects/Character/Character.h
        Source/Core/Objects/Character/PlayerCharacter.cpp
        Source/Core/Objects/Character/PlayerCharacter.h
        Source/Core/Interfaces/ICoreEvents.cpp
        Source/Core/Interfaces/ICoreEvents.h
        Source/Core/Interfaces/IKeyEvents.cpp
        Source/Core/Interfaces/IKeyEvents.h
        Source/Core/MovementMode.h
        Source/Core/Interfaces/IDisposable.cpp
        Source/Core/Interfaces/IDisposable.h
        Source/Game/MonkeyLevel.cpp
        Source/Game/MonkeyLevel.h
        Source/Game/BallsLevel.cpp
        Source/Game/BallsLevel.h
        Source/Core/Graphics/ShaderInfo.cpp
        Source/Core/Graphics/ShaderInfo.h
        Source/Core/ObjectComponents/LightComponent.cpp
        Source/Core/ObjectComponents/LightComponent.h
        Source/Core/Graphics/Model.cpp
        Source/Core/Graphics/Model.h
        Source/Resources/Models/MOD_DefaultSphere.h
        Source/Resources/Models/MOD_Bush.h
)

add_custom_target(copyResources
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copyResources.cmake
)
add_dependencies(ZPG copyResources)

find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
target_include_directories(ZPG PRIVATE
        /opt/homebrew/include
        ${CMAKE_SOURCE_DIR}/vendor
        ${CMAKE_SOURCE_DIR}/Source
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
    set_source_files_properties(Source/Core/UI/imgui_impl_metal.cpp PROPERTIES
            LANGUAGE CXX
    )
endif ()