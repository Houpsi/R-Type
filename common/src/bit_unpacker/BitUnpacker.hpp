/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** BitUnpacker
*/

#ifndef R_TYPE_BITUNPACKER_HPP
#define R_TYPE_BITUNPACKER_HPP

#include <cstdint>
#include <vector>
#include <cstring>

namespace cmn {

    class BitUnpacker
    {
      public:
        BitUnpacker(std::vector<uint8_t> &buffer, size_t size);

        uint32_t readBits(uint8_t numBits);
        bool readBool();
        uint8_t readUInt8();
        uint16_t readUInt16();
        uint32_t readUInt32();
        uint32_t readRangedUInt(uint32_t minVal, uint32_t maxVal);
        float readFloat(float minValue, float maxValue, uint32_t precision);

      private:
        std::vector<uint8_t> _buffer;
        size_t _bufferSize;
        size_t _bitPosition = 0;
    };

}// namespace cmn

#endif// R_TYPE_BITUNPACKER_HPP
