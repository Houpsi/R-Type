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
    constexpr int volumeMusic = 100;
    constexpr std::string_view folderSound = "./assets/sound/";
    constexpr std::array<std::string_view, 2> idToSound = {"shoot", "theme"};
}



#endif// R_TYPE_ECSCONSTANT_HPP
