cmake_minimum_required(VERSION 3.10)

project(r-type_client)

set(CMAKE_CXX_STANDARD 20)

include_directories(. ecs/components ecs/systems ecs/)

add_subdirectory(ecs)

