/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** CustomPacket
*/
#ifndef R_TYPE_CUSTOMPACKET_HPP
#define R_TYPE_CUSTOMPACKET_HPP

#include "SFML/Network/Packet.hpp"

namespace cmn {

    class CustomPacket : public sf::Packet
    {
      public:
        const void* onSend(std::size_t &size) override;
        void onReceive(const void *data, std::size_t size) override;

      private:
    };

}// namespace server

#endif// R_TYPE_CUSTOMPACKET_HPP
