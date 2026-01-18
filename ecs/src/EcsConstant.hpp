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
#include <cstdint>

namespace ecs {

    namespace dir {
        constexpr float left = -1.0f;
        constexpr float right = 1.0f;
        constexpr float up = -1.0f;
        constexpr float down = 1.0f;
        constexpr float neutral = 0.0f;
        constexpr float normalized45degreesUp = 0.5f;
        constexpr float normalized23degreesUp = 0.25f;
        constexpr float normalized45degreesDown = -0.5f;
        constexpr float normalized23degreesDown = -0.25f;
    }

    constexpr int volumeMusic = 100;
    constexpr std::string_view folderSound = "./assets/sound/";
    constexpr std::array<std::string_view, 5> idToSound = {"shoot", "theme", "explosion", "boss1", "power_up"};
    constexpr int idExplosionMusic = 3;
    constexpr int idPowerUpMusic = 5;
    constexpr int nbAmmoShotgun = 5;
    constexpr int nbAmmoGatling = 20;
    constexpr int nbAmmoNormalGun = 99999;


    static constexpr int scoreKillMonster = 100;

    static constexpr int MAX_ENTITIES = 6;
    static constexpr int MAX_DEPTH = 6;

    constexpr uint16_t windowWidth = 1920;
    constexpr uint16_t windowHeight = 1080;
}


#endif // R_TYPE_ECSCONSTANT_HPP
