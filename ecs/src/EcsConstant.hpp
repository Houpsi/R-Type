/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** EcsConstant
*/

#ifndef R_TYPE_ECSCONSTANT_HPP
#define R_TYPE_ECSCONSTANT_HPP
#include <array>
#include <string_view>

namespace ecs {

    constexpr int left = 0;
    constexpr int right = 1;
    constexpr int up = 2;
    constexpr int down = 3;

    constexpr int volumeMusic = 100;
    constexpr std::string_view folderSound = "./assets/sound/";
    constexpr std::array<std::string_view, 3> idToSound = {"shoot", "theme", "explosion"};

    static constexpr int MAX_ENTITIES = 6;
    static constexpr int MAX_DEPTH = 6;

    constexpr uint16_t windowWidth = 1920;
    constexpr uint16_t windowHeight = 1080;
}



#endif// R_TYPE_ECSCONSTANT_HPP
