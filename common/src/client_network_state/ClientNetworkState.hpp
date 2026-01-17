/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ClientNetworkState
*/

#ifndef R_TYPE_CLIENTNETWORKSTATE_HPP
#define R_TYPE_CLIENTNETWORKSTATE_HPP

#include <cstdint>
#include <unordered_set>

namespace cmn {

    using clientNetworkState = struct clientNetworkState
    {
        uint32_t lastProcessedSequence = 0;
        std::unordered_set<uint32_t> processedSequences;
    };

}

#endif// R_TYPE_CLIENTNETWORKSTATE_HPP
