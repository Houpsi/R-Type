add_executable(rtype_client_tests
        TestClient.cpp
)

target_link_libraries(rtype_client_tests
        PRIVATE
        r-type_ecs_lib
        r-type_common_lib
        r-type_client_lib
        gtest
        gtest_main
)

target_include_directories(rtype_client_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME MyTests COMMAND rtype_client_tests)
