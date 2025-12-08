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

include_directories(../ecs Components Systems )

add_executable(r-type_client
        ../Game.cpp
        ../Game.hpp
        Entity.cpp
        Entity.hpp
        EcsManager.cpp
        EcsManager.hpp

        systems/System.cpp
        systems/System.hpp
        systems/RenderSystem.cpp
        systems/RenderSystem.hpp
        systems/MovementSystem.cpp
        systems/MovementSystem.hpp
        systems/InputSystem.cpp
        systems/InputSystem.hpp

        components/Sound.cpp
        components/Sound.hpp
        components/Collider.cpp
        components/Collider.hpp
        components/InputPlayer.cpp
        components/InputPlayer.hpp
        components/Health.cpp
        components/Health.hpp
        components/Position.cpp
        components/Position.hpp
        components/Component.cpp
        components/Component.hpp
        components/Sprite.cpp
        components/Sprite.hpp
        components/Enemy.cpp
        components/Enemy.hpp

        ../main.cpp
)

target_link_libraries(r-type_client PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

add_subdirectory(tests)
