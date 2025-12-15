cmake_minimum_required(VERSION 3.30.8)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

project(
        r-type_client
)

add_subdirectory(src)
add_subdirectory(tests)
