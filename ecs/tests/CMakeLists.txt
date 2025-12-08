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
            ../../Game.cpp
            ../../Game.hpp

            ../Entity.cpp
            ../Entity.hpp
            ../EcsManager.cpp
            ../EcsManager.hpp

            ../systems/System.cpp
            ../systems/System.hpp
            ../systems/RenderSystem.cpp
            ../systems/RenderSystem.hpp
            ../systems/MovementSystem.cpp
            ../systems/MovementSystem.hpp
            ../systems/InputSystem.cpp
            ../systems/InputSystem.hpp

            ../components/Sound.cpp
            ../components/Sound.hpp
            ../components/Collider.cpp
            ../components/Collider.hpp
            ../components/InputPlayer.cpp
            ../components/InputPlayer.hpp
            ../components/Health.cpp
            ../components/Health.hpp
            ../components/Position.cpp
            ../components/Position.hpp
            ../components/Component.cpp
            ../components/Component.hpp
            ../components/Sprite.cpp
            ../components/Sprite.hpp
            ../components/Enemy.cpp
            ../components/Enemy.hpp
    )

    add_executable(r-type_client_tests
            TestsEcsManager.cpp
            TestsHealth.cpp
            TestsPosition.cpp
            TestsSprite.cpp
            TestsInputPlayer.cpp
    )
    target_link_libraries(r-type_client_tests PRIVATE
            gtest
            gtest_main
            sfml-graphics
            sfml-window
            sfml-system
            ECSLib
    )

    target_include_directories(r-type_client PRIVATE ../../GameEngine)

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