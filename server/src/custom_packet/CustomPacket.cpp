/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** CustomPacket
*/
#include "CustomPacket.hpp"

namespace server {

    const void *CustomPacket::onSend(size_t &size)
    {
        // TODO -> data encryption
        return Packet::onSend(size);
    }

    void CustomPacket::onReceive(const void *data, std::size_t size) 
    {
        //TODO -> data decryption
        Packet::onReceive(data, size); 
    }
    
}// namespace server