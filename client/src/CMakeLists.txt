add_library(r-type_client_lib
        game/Game.cpp
        game/Game.hpp
        parser/Parser.cpp
        parser/Parser.hpp
        client/Client.cpp
        client/Client.hpp
        game/Game.cpp
        game/Game.hpp
)

target_include_directories(r-type_client_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_client_lib
        PUBLIC
        SFML::Network
        r-type_ecs_lib
        r-type_common_lib
)

add_executable(r-type_client
        main.cpp
        game/Game.cpp
        game/Game.hpp
        parser/Parser.cpp
        parser/Parser.hpp
        client/Client.cpp
        client/Client.hpp
        game/Game.cpp
        game/Game.hpp
)

target_link_libraries(r-type_client PRIVATE r-type_client_lib r-type_ecs_lib r-type_common_lib)