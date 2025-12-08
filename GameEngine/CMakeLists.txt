cmake_minimum_required(VERSION 3.10)

project(ECSLib)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(. Components Systems )

add_executable(r-type_client
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

        ../main.cpp
        ../main.hpp
)

target_link_libraries(r-type_client PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

add_subdirectory(tests)
