/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** EntityType
*/

#ifndef R_TYPE_ENTITYTYPE_HPP
#define R_TYPE_ENTITYTYPE_HPP

#include <cstdint>
namespace cmn {

    enum class EntityType: uint8_t
    {
        Player,
        Monster,
        PlayerProjectile,
        MonsterProjectile,
    };

}

#endif// R_TYPE_ENTITYTYPE_HPP
