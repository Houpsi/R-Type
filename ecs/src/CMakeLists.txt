add_library(r-type_ecs_lib
        systems/System.cpp
        systems/System.hpp
        systems/RenderSystem.cpp
        systems/RenderSystem.hpp
        systems/MovementSystem.cpp
        systems/MovementSystem.hpp
        systems/InputSystem.cpp
        systems/InputSystem.hpp
        systems/CollisionSystem.cpp
        systems/CollisionSystem.hpp
        components/Sound.cpp
        components/Sound.hpp
        components/Collision.cpp
        components/Collision.hpp
        components/InputPlayer.cpp
        components/InputPlayer.hpp
        components/Health.cpp
        components/Health.hpp
        components/Position.cpp
        components/Position.hpp
        components/Component.cpp
        components/Component.hpp
        Entity.cpp
        Entity.hpp
        EcsManager.cpp
        EcsManager.hpp
        components/Sprite.cpp
        components/Sprite.hpp
        components/Sprite.hpp
        components/Enemy.cpp
        components/Enemy.hpp
        systems/ShootSystem.cpp
        systems/ShootSystem.hpp
        components/Destroy.cpp
        components/Destroy.hpp
        systems/DestroySystem.cpp
        systems/DestroySystem.hpp
)

target_include_directories(r-type_ecs_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_ecs_lib PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(r-type_server PRIVATE r-type_ecs_lib)