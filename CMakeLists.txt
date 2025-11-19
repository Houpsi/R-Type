cmake_minimum_required(VERSION 3.10)
project(R_Type)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(R_Type
        main.cpp
        main.hpp)
