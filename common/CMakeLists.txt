cmake_minimum_required(VERSION 3.28.3)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

project(
        r-type_common
)

CPMAddPackage(
        NAME LZ4
        GITHUB_REPOSITORY lz4/lz4
        GIT_TAG v1.10.0
        SOURCE_SUBDIR build/cmake
)

add_subdirectory(src)
add_subdirectory(test)
