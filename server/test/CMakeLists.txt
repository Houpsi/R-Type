include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(rtype_server_tests
        TestParser.cpp
        TestServer.cpp
)

target_link_libraries(rtype_server_tests
        PRIVATE
        r-type_server_lib
        gtest
        gtest_main
)

target_include_directories(rtype_server_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME MyTests COMMAND rtype_server_tests)
