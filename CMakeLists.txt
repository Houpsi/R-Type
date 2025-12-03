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
include_directories(. ecs/components ecs/systems ecs/)

add_subdirectory(GameEngine)

add_executable(R_Type
        main.cpp
        main.hpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(R_Type PRIVATE
        ECSLib
        sfml-graphics
        sfml-window
        sfml-system
)

# ------------------------
# TESTS - GOOGLE TESTS
# ------------------------
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(COPY Tests/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    enable_testing()

    add_executable(EngineTests
            Tests/TestsEcsManager.cpp
            Tests/TestsHealth.cpp
            Tests/TestsPosition.cpp
            Tests/TestsSprite.cpp
            Tests/TestsInputPlayer.cpp
    )
    target_link_libraries(EngineTests PRIVATE
            gtest
            gtest_main
            ECSLib
            sfml-graphics
            sfml-window
            sfml-system
    )

    set_target_properties(EngineTests PROPERTIES
            COMPILE_FLAGS "--coverage -g -O0"
            LINK_FLAGS "--coverage"
    )

    add_test(NAME EngineTests COMMAND EngineTests)

    add_custom_target(run_tests
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            DEPENDS EngineTests
    )

endif()
