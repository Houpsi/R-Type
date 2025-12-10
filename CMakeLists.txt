cmake_minimum_required(VERSION 3.30.8)

project(
        R_Type
)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

add_subdirectory(server)

add_executable(r-type_client
        main.cpp
        Game.cpp
        Game.hpp
        ecs/src/systems/System.cpp
        ecs/src/systems/System.hpp
        ecs/src/systems/RenderSystem.cpp
        ecs/src/systems/RenderSystem.hpp
        ecs/src/systems/MovementSystem.cpp
        ecs/src/systems/MovementSystem.hpp
        ecs/src/systems/InputSystem.cpp
        ecs/src/systems/InputSystem.hpp
        ecs/src/systems/CollisionSystem.cpp
        ecs/src/systems/CollisionSystem.hpp
        ecs/src/components/Sound.cpp
        ecs/src/components/Sound.hpp
        ecs/src/components/Collision.cpp
        ecs/src/components/Collision.hpp
        ecs/src/components/InputPlayer.cpp
        ecs/src/components/InputPlayer.hpp
        ecs/src/components/Health.cpp
        ecs/src/components/Health.hpp
        ecs/src/components/Position.cpp
        ecs/src/components/Position.hpp
        ecs/src/components/Component.cpp
        ecs/src/components/Component.hpp
        ecs/src/Entity.cpp
        ecs/src/Entity.hpp
        ecs/src/EcsManager.cpp
        ecs/src/EcsManager.hpp
        ecs/src/components/Sprite.cpp
        ecs/src/components/Sprite.hpp
        ecs/src/components/Sprite.hpp
        ecs/src/components/Enemy.cpp
        ecs/src/components/Enemy.hpp
        ecs/src/systems/ShootSystem.cpp
        ecs/src/systems/ShootSystem.hpp
        ecs/src/components/Destroy.cpp
        ecs/src/components/Destroy.hpp
        ecs/src/systems/DestroySystem.cpp
        ecs/src/systems/DestroySystem.hpp)

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system)
enable_testing()
