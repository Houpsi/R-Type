/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DeleteEntityPacket
*/

#ifndef R_TYPE_DELETEENTITYDATA_HPP
#define R_TYPE_DELETEENTITYDATA_HPP

#include "SFML/Network/Packet.hpp"
#include <cstdint>
namespace cmn {

    using deleteEntityData = struct deleteEntityData {
        uint32_t entityId;
    };

}// namespace cmn

#endif// R_TYPE_DELETEENTITYDATA_HPP
