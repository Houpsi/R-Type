add_library(r-type_client_lib
        game_renderer/GameRenderer.cpp
        game_renderer/GameRenderer.hpp
        parser/Parser.cpp
        parser/Parser.hpp
        client/Client.cpp
        client/Client.hpp
        game_renderer/GameRenderer.cpp
        game_renderer/GameRenderer.hpp
        input_manager/InputManager.cpp
        input_manager/InputManager.hpp
)

target_include_directories(r-type_client_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_client_lib
        PUBLIC
        SFML::Network
        r-type_ecs_lib
        r-type_common_lib
        config++
)

add_executable(r-type_client
        main.cpp
        game_renderer/GameRenderer.cpp
        game_renderer/GameRenderer.hpp
        parser/Parser.cpp
        parser/Parser.hpp
        client/Client.cpp
        client/Client.hpp
        game_renderer/GameRenderer.cpp
        game_renderer/GameRenderer.hpp
        input_manager/InputManager.cpp
        input_manager/InputManager.hpp
)

target_link_libraries(r-type_client PRIVATE r-type_client_lib r-type_ecs_lib r-type_common_lib config++)