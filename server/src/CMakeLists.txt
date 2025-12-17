add_library(r-type_server_lib
        parser/Parser.cpp
        parser/Parser.hpp
        server/Server.cpp
        server/Server.hpp
        game/Game.cpp
        game/Game.hpp
        level/Level.cpp
        level/Level.hpp
        level_manager/LevelManager.cpp
        level_manager/LevelManager.hpp
)

target_include_directories(r-type_server_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_server_lib
        PUBLIC
        SFML::Network
        r-type_ecs_lib
        r-type_common_lib
)

add_executable(r-type_server
        main.cpp
        parser/Parser.cpp
        parser/Parser.hpp
        server/Server.cpp
        server/Server.hpp
        game/Game.cpp
        game/Game.hpp
        level/Level.cpp
        level/Level.hpp
        level_manager/LevelManager.cpp
        level_manager/LevelManager.hpp
        factory/EntityProduct.cpp
        factory/EntityProduct.hpp
        factory/Player.cpp
        factory/Player.hpp
        factory/EntityFactory.cpp
        factory/EntityFactory.hpp
        factory/PlayerFactory.cpp
        factory/PlayerFactory.hpp
        factory/EnemyProduct.cpp
        factory/EnemyProduct.hpp
)

target_link_libraries(r-type_server PRIVATE r-type_server_lib r-type_ecs_lib r-type_common_lib)