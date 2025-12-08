option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    enable_testing()

    add_library(ECSLib
            ../Game.cpp
            ../Game.hpp

            ../Entity.cpp
            ../Entity.hpp
            ../EcsManager.cpp
            ../EcsManager.hpp

            ../Systems/System.cpp
            ../Systems/System.hpp
            ../Systems/RenderSystem.cpp
            ../Systems/RenderSystem.hpp
            ../Systems/MovementSystem.cpp
            ../Systems/MovementSystem.hpp
            ../Systems/InputSystem.cpp
            ../Systems/InputSystem.hpp

            ../Components/Sound.cpp
            ../Components/Sound.hpp
            ../Components/Collider.cpp
            ../Components/Collider.hpp
            ../Components/InputPlayer.cpp
            ../Components/InputPlayer.hpp
            ../Components/Health.cpp
            ../Components/Health.hpp
            ../Components/Position.cpp
            ../Components/Position.hpp
            ../Components/Component.cpp
            ../Components/Component.hpp
            ../Components/Sprite.cpp
            ../Components/Sprite.hpp
            ../Components/Enemy.cpp
            ../Components/Enemy.hpp
    )

    add_executable(r-type_client_tests
            TestsEcsManager.cpp
            TestsHealth.cpp
            TestsPosition.cpp
            TestsSprite.cpp
            TestsInputPlayer.cpp
    )
    target_link_libraries(r-type_client_tests PRIVATE
            ECSLib
            gtest
            gtest_main
            sfml-graphics
            sfml-window
            sfml-system
    )

    target_include_directories(r-type_client PRIVATE ../)

#    set_target_properties(r-type_client_tests PROPERTIES
#            COMPILE_FLAGS "--coverage -g -O0"
#            LINK_FLAGS "--coverage"
#    )

    add_test(NAME r-type_client_tests COMMAND r-type_client_tests)

    add_custom_target(run_tests
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            DEPENDS r-type_client_tests
    )

endif()