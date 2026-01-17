/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ReliablePacket
*/

#ifndef R_TYPE_RELIABLEPACKET_HPP
#define R_TYPE_RELIABLEPACKET_HPP

#include "custom_packet/CustomPacket.hpp"
#include <chrono>

namespace cmn {

    using reliablePacket = struct reliablePacket
    {
        CustomPacket packet;
        std::chrono::steady_clock::time_point lastSentTime;
        uint32_t retryCount = 0;
    };

}

#endif// R_TYPE_RELIABLEPACKET_HPP
