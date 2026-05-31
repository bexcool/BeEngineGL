cmake_minimum_required(VERSION 3.30)
project(BeEngineGL)

set(CMAKE_CXX_STANDARD 20)

add_library(BeEngineGL SHARED
        #Source/main.cpp
        Source/BECore/Application.cpp
        Source/BECore/Application.h
        Source/BECore/Physics/PhysicsEngine.cpp
        Source/BECore/Physics/PhysicsEngine.h
        Source/BECore/Graphics/Renderer.cpp
        Source/BECore/Graphics/Renderer.h
        Source/BECore/Graphics/ShaderProgram.cpp
        Source/BECore/Graphics/ShaderProgram.h
        Source/BECore/Graphics/Shader.cpp
        Source/BECore/Graphics/Shader.h
        Source/BECore/ObjectComponents/ModelComponent.cpp
        Source/BECore/ObjectComponents/ModelComponent.h
        Source/BECore/ObjectComponents/ColliderComponent.cpp
        Source/BECore/ObjectComponents/ColliderComponent.h
        Source/BECore/Math/Transform.cpp
        Source/BECore/Math/Transform.h
        Source/BECore/Math/Location.cpp
        Source/BECore/Math/Location.h
        Source/BECore/Math/Rotation.cpp
        Source/BECore/Math/Rotation.h
        Source/BECore/Math/Scale.cpp
        Source/BECore/Math/Scale.h
        Source/BECore/Level.cpp
        Source/BECore/Level.h
        Source/BECore/Graphics/Window.cpp
        Source/BECore/Graphics/Window.h
        Source/BECore/Controllers/Controller.cpp
        Source/BECore/Controllers/Controller.h
        Source/BECore/Events/InputManager.cpp
        Source/BECore/Events/InputManager.h
        Source/BECore/Events/EventArgs.cpp
        Source/BECore/Events/EventArgs.h
        Source/BECore/Events/KeyboardKeyEventArgs.cpp
        Source/BECore/Events/KeyboardKeyEventArgs.h
        Source/Game/TestLevel.cpp
        Source/Game/TestLevel.h
        Source/BECore/GameLoop.cpp
        Source/BECore/GameLoop.h
        Source/BECore/logger.c
        Source/BECore/logger.h
        Source/BECore/ObjectComponents/CameraComponent.cpp
        Source/BECore/ObjectComponents/CameraComponent.h
        Source/BECore/Objects/GameObject.cpp
        Source/BECore/Objects/GameObject.h
        Source/BECore/Events/MouseKeyEventArgs.cpp
        Source/BECore/Events/MouseKeyEventArgs.h
        Source/BECore/ObjectComponents/GameObjectComponent.cpp
        Source/BECore/ObjectComponents/GameObjectComponent.h
        Source/BECore/Controllers/PlayerController.cpp
        Source/BECore/Controllers/PlayerController.h
        Source/BECore/Events/EventDispatcher.cpp
        Source/BECore/Events/EventDispatcher.h
        Source/BECore/Objects/Character/Character.cpp
        Source/BECore/Objects/Character/Character.h
        Source/BECore/Objects/Character/PlayerCharacter.cpp
        Source/BECore/Objects/Character/PlayerCharacter.h
        Source/BECore/Interfaces/ICoreEvents.cpp
        Source/BECore/Interfaces/ICoreEvents.h
        Source/BECore/Interfaces/IKeyEvents.cpp
        Source/BECore/Interfaces/IKeyEvents.h
        Source/BECore/MovementMode.h
        Source/BECore/Interfaces/IDisposable.cpp
        Source/BECore/Interfaces/IDisposable.h
        Source/Game/MonkeyLevel.cpp
        Source/Game/MonkeyLevel.h
        Source/Game/BallsLevel.cpp
        Source/Game/BallsLevel.h
        Source/BECore/Graphics/ShaderInfo.cpp
        Source/BECore/Graphics/ShaderInfo.h
        Source/BECore/ObjectComponents/LightComponent.cpp
        Source/BECore/ObjectComponents/LightComponent.h
        Source/BECore/Graphics/Model.cpp
        Source/BECore/Graphics/Model.h
        Source/BECore/Math/Vector3.cpp
        Source/BECore/Math/Vector3.h
        Source/BECore/Graphics/Light.h
        Source/Libs/tiny_obj_loader.h
        Source/Resources/Assets/Models/MOD_F1.h
        Source/Libs/stb_image.h
        Source/Resources/Assets/Models/MOD_Plane.h
        Source/Resources/Assets/Models/Shrek/MOD_Shrek.h
        Source/Resources/Assets/Models/Shrek/MOD_Fiona.h
        Source/Resources/Assets/Models/Shrek/MOD_Toilet.h
        Source/BECore/Graphics/SkyBox/SkyBoxModel.cpp
        Source/BECore/Graphics/SkyBox/SkyBoxModel.h
        Source/Resources/Assets/Models/MOD_SkyBox.h
        Source/BECore/Graphics/SkyBox/SkyBoxShaderProgram.cpp
        Source/BECore/Graphics/SkyBox/SkyBoxShaderProgram.h
        Source/Game/SolarSystemLevel.cpp
        Source/Game/SolarSystemLevel.h
        Source/Resources/Assets/Models/MOD_login_pav0531.h
        Source/BECore/Graphics/CubeMap.h
        Source/Resources/Assets/Models/MOD_Sphere.h
        Source/BECore/Graphics/Material/Material.cpp
        Source/BECore/Graphics/Material/Material.h
        Source/BECore/Graphics/Material/MaterialParameter.cpp
        Source/BECore/Graphics/Material/MaterialParameter.h
        Source/BECore/Graphics/Material/Texture.cpp
        Source/BECore/Graphics/Material/Texture.h
        Source/Resources/Assets/Models/Shrek/MAT_Shrek.h
        Source/Resources/Assets/Models/Shrek/TEX_Shrek.h
        Source/Resources/Assets/Textures/TEX_Default.h
        Source/BECore/Graphics/Material/MaterialData.h
        Source/BECore/ObjectComponents/SplineComponent.cpp
        Source/BECore/ObjectComponents/SplineComponent.h
        Source/BECore/Math/CurvePoint.h
        Source/Game/WhackMoleLevel.cpp
        Source/Game/WhackMoleLevel.h
        Source/BECore/ObjectComponents/CollisionBoxComponent.cpp
        Source/BECore/ObjectComponents/CollisionBoxComponent.h
)

add_custom_target(copyResources
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copyResources.cmake
)
add_dependencies(BeEngineGL copyResources)

target_compile_definitions(BeEngineGL PRIVATE BE_BUILD_DLL)

find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
target_include_directories(BeEngineGL PUBLIC
        /opt/homebrew/include
        ${CMAKE_SOURCE_DIR}/vendor
        ${CMAKE_SOURCE_DIR}/Source
        ${CMAKE_SOURCE_DIR}/ThirdParty/JoltPhysics
)
if (APPLE)
    target_link_directories(BeEngineGL PUBLIC /opt/homebrew/lib)
    target_compile_definitions(BeEngineGL PUBLIC GL_SILENCE_DEPRECATION)
    target_link_libraries(BeEngineGL PUBLIC
            glfw
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            "-lGLEW"
            "${CMAKE_SOURCE_DIR}/ThirdParty/JoltPhysics/libJolt.dylib"
    )
    set_source_files_properties(Source/BECore/UI/imgui_impl_metal.cpp PROPERTIES
            LANGUAGE CXX
    )
endif ()