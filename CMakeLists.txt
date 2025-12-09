cmake_minimum_required(VERSION 3.10)

project(r-type_client)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
include_directories(. ecs/components ecs/systems ecs/)

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
        ecs/components/Velocity.cpp
        ecs/components/Velocity.hpp
        ecs/components/Shoot.cpp
        ecs/components/Shoot.hpp
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
        ecs/systems/VelocitySystem.cpp
        ecs/systems/VelocitySystem.hpp
        )

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system)
