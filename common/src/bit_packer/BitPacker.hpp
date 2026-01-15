/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** BitPacker
*/

#ifndef R_TYPE_BITPACKER_HPP
#define R_TYPE_BITPACKER_HPP

#include <vector>
#include <cstdint>

namespace cmn {

    class BitPacker
    {
      public:
        void writeBits(uint32_t value, uint8_t numBits);
        void writeBool(bool value);
        void writeUInt8(uint8_t value);
        void writeUInt16(uint16_t value);
        void writeUInt32(uint32_t value);
        void writeRangedUInt(uint32_t value, uint32_t minVal, uint32_t maxVal);
        void writeFloat(float value, float minValue, float maxValue, uint32_t precision);
        [[nodiscard]] const std::vector<uint8_t> &getBuffer() const;
        [[nodiscard]] size_t getByteSize() const;
        [[nodiscard]] size_t getBitSize() const;

      private:
        std::vector<uint8_t> _buffer;
        size_t _bitPosition = 0;
    };

}// namespace cmn

#endif// R_TYPE_BITPACKER_HPP
