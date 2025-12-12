add_executable(rtype_ecs_tests
        TestsEcsManager.cpp
        TestsHealth.cpp
        TestsInputPlayer.cpp
        TestsPosition.cpp
        TestsSprite.cpp
        TestsAnimation.cpp
        TestsCollision.cpp
        TestsVelocity.cpp
)

target_link_libraries(rtype_ecs_tests
        PRIVATE
        r-type_ecs_lib
        gtest
        gtest_main
)

target_include_directories(rtype_ecs_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME MyTests COMMAND rtype_ecs_tests)
