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
        ecs/systems/System.cpp
        ecs/systems/System.hpp
        ecs/systems/RenderSystem.cpp
        ecs/systems/RenderSystem.hpp
        ecs/systems/MovementSystem.cpp
        ecs/systems/MovementSystem.hpp
        ecs/systems/InputSystem.cpp
        ecs/systems/InputSystem.hpp
        ecs/systems/CollisionSystem.cpp
        ecs/systems/CollisionSystem.hpp
        ecs/components/Sound.cpp
        ecs/components/Sound.hpp
        ecs/components/Collision.cpp
        ecs/components/Collision.hpp
        ecs/components/InputPlayer.cpp
        ecs/components/InputPlayer.hpp
        ecs/components/Health.cpp
        ecs/components/Health.hpp
        ecs/components/Position.cpp
        ecs/components/Position.hpp
        ecs/components/Component.cpp
        ecs/components/Component.hpp
        ecs/Entity.cpp
        ecs/Entity.hpp
        ecs/EcsManager.cpp
        ecs/EcsManager.hpp
        ecs/components/Sprite.cpp
        ecs/components/Sprite.hpp
        ecs/components/Sprite.hpp
        ecs/components/Enemy.cpp
        ecs/components/Enemy.hpp
        ecs/systems/ShootSystem.cpp
        ecs/systems/ShootSystem.hpp
        ecs/components/Destroy.cpp
        ecs/components/Destroy.hpp
        ecs/systems/DestroySystem.cpp
        ecs/systems/DestroySystem.hpp)

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system)
enable_testing()
