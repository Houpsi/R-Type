/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** DataTranslator
*/

#ifndef R_TYPE_DATATRANSLATOR_HPP
#define R_TYPE_DATATRANSLATOR_HPP

#include "EcsManager.hpp"
#include "packet_data/PacketData.hpp"

namespace cmn {

    class DataTranslator
    {
        void translate(ecs::EcsManager &ecs, packetData &data);
        void _injectInput(ecs::EcsManager &ecs, inputPacket &input, int id);
    };

}// namespace cmn

#endif// R_TYPE_DATATRANSLATOR_HPP
