/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** KeyState
*/
#ifndef R_TYPE_KEYSTATE_HPP
#define R_TYPE_KEYSTATE_HPP

#include <cstdint>
namespace cmn {

    enum class KeyState : uint8_t {
        Released,
        Pressed,
    };

}

#endif// R_TYPE_KEYSTATE_HPP
