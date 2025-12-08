cmake_minimum_required(VERSION 3.10)

project(R_Type)

set(CMAKE_CXX_STANDARD 20)

include_directories(. GameEngine/Components GameEngine/Systems GameEngine/)

add_subdirectory(GameEngine)

#add_executable(R_Type
#        main.cpp
#        main.hpp
#)

#target_link_libraries(R_Type PRIVATE
#        sfml-graphics
#        sfml-window
#        sfml-system
#)
