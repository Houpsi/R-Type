set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
        NAME SFML
        GITHUB_REPOSITORY SFML/SFML
        GIT_TAG 3.0.2
)

add_library(r-type_server_lib
        parser/Parser.cpp
        parser/Parser.hpp
        server/Server.cpp
        server/Server.hpp
)

target_include_directories(r-type_server_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_server_lib PUBLIC SFML::Network)

add_executable(r-type_server
        main.cpp
        parser/Parser.cpp
        parser/Parser.hpp
        server/Server.cpp
        server/Server.hpp
)

target_link_libraries(r-type_server PRIVATE r-type_server_lib)