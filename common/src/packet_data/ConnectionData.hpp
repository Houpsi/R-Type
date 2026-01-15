/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ConnectionData
*/

#ifndef R_TYPE_CONNECTIONDATA_HPP
#define R_TYPE_CONNECTIONDATA_HPP

#include "SFML/Network/Packet.hpp"
#include <cstdint>
namespace cmn {

    using connectionData = struct ConnectionData
    {
        uint32_t playerId;
    };

}// namespace cmn

#endif// R_TYPE_CONNECTIONDATA_HPP
