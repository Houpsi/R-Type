add_executable(rtype_client_tests
)

target_link_libraries(rtype_client_tests
        PRIVATE
        r-type_ecs_lib
        gtest
        gtest_main
)

target_include_directories(rtype_client_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME MyTests COMMAND rtype_client_tests)
