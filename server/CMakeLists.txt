cmake_minimum_required(VERSION 3.28.3)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

project(
        r-type_server
)

CPMAddPackage(
        NAME LIBCONFIG
        GITHUB_REPOSITORY hyperrealm/libconfig
        GIT_TAG v1.8.2
)

add_subdirectory(src)
#add_subdirectory(tests)
