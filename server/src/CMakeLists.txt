add_library(r-type_server_lib
        parser/Parser.cpp
        parser/Parser.hpp
        server/Server.cpp
        server/Server.hpp
        game/Game.cpp
        game/Game.hpp
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
)

target_link_libraries(r-type_server PRIVATE r-type_server_lib r-type_ecs_lib r-type_common_lib)