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
include_directories(. GameEngine/Components GameEngine/Systems GameEngine/)

add_executable(r-type_client
        main.cpp
        main.hpp
        Game.cpp
        Game.hpp
        GameEngine/Systems/System.cpp
        GameEngine/Systems/System.hpp
        GameEngine/Systems/RenderSystem.cpp
        GameEngine/Systems/RenderSystem.hpp
        GameEngine/Systems/MovementSystem.cpp
        GameEngine/Systems/MovementSystem.hpp
        GameEngine/Systems/InputSystem.cpp
        GameEngine/Systems/InputSystem.hpp
        GameEngine/Components/Sound.cpp
        GameEngine/Components/Sound.hpp
        GameEngine/Components/Collider.cpp
        GameEngine/Components/Collider.hpp
        GameEngine/Components/InputPlayer.cpp
        GameEngine/Components/InputPlayer.hpp
        GameEngine/Components/Health.cpp
        GameEngine/Components/Health.hpp
        GameEngine/Components/Position.cpp
        GameEngine/Components/Position.hpp
        GameEngine/Components/Component.cpp
        GameEngine/Components/Component.hpp
        GameEngine/Entity.cpp
        GameEngine/Entity.hpp
        GameEngine/EcsManager.cpp
        GameEngine/EcsManager.hpp
        GameEngine/Components/Sprite.cpp
        GameEngine/Components/Sprite.hpp
        GameEngine/Components/Sprite.hpp
        GameEngine/Components/Enemy.cpp
        GameEngine/Components/Enemy.hpp)

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system)
