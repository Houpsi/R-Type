cmake_minimum_required(VERSION 3.10)

project(ECSLib)

set(CMAKE_CXX_STANDARD 14)

include_directories(. Components Systems )

add_library(ECSLib SHARED
        Game.cpp
        Game.hpp
        Entity.cpp
        Entity.hpp
        EcsManager.cpp
        EcsManager.hpp

        Systems/System.cpp
        Systems/System.hpp
        Systems/RenderSystem.cpp
        Systems/RenderSystem.hpp
        Systems/MovementSystem.cpp
        Systems/MovementSystem.hpp
        Systems/InputSystem.cpp
        Systems/InputSystem.hpp

        Components/Sound.cpp
        Components/Sound.hpp
        Components/Collider.cpp
        Components/Collider.hpp
        Components/InputPlayer.cpp
        Components/InputPlayer.hpp
        Components/Health.cpp
        Components/Health.hpp
        Components/Position.cpp
        Components/Position.hpp
        Components/Component.cpp
        Components/Component.hpp
        Components/Sprite.cpp
        Components/Sprite.hpp
        Components/Enemy.cpp
        Components/Enemy.hpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
