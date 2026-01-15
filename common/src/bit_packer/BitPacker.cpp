/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** BitPacker
*/

#include "BitPacker.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include <cstring>
#include "constants/BitPackingConstants.hpp"
#include <limits>

namespace cmn {

    void BitPacker::writeBits(uint32_t value, uint8_t numBits)
    {
        if (numBits == 0 || numBits > maxBits) {
            return;
        }

        value &= (numBits == maxBits) ? bitMask : ((1U << numBits) - 1);

        while (numBits > 0) {
            size_t const byteIndex = _bitPosition / byteSize;
            size_t const bitOffset = _bitPosition % byteSize;

            if (byteIndex >= _buffer.size()) {
                _buffer.push_back(0);
            }

            uint32_t const bitsAvailable = byteSize - bitOffset;
            uint32_t const bitsToWrite = std::min(static_cast<uint32_t>(numBits), bitsAvailable);

            _buffer[byteIndex] |= (value << bitOffset) & lowestByteMask;
            value >>= bitsToWrite;
            numBits -= bitsToWrite;
            _bitPosition += bitsToWrite;
        }
    }

    void BitPacker::writeBool(bool value)
    {
        writeBits(value ? 1 : 0, 1);
    }

    void BitPacker::writeUInt8(uint8_t value)
    {
        writeBits(value, uint8Size);
    }

    void BitPacker::writeUInt16(uint16_t value)
    {
        writeBits(value, uint16Size);
    }

    void BitPacker::writeUInt32(uint32_t value)
    {
        writeBits(value, uint32Size);
    }

    void BitPacker::writeRangedUInt(uint32_t value, uint32_t minVal, uint32_t maxVal)
    {
        uint32_t const range = maxVal - minVal;
        uint32_t bitsNeeded = 0;
        uint32_t shiftedValue  = 1U << bitsNeeded;
        while ((shiftedValue) <= range) {
            bitsNeeded++;
            if (shiftedValue > INT32_MAX) {
                break;
            }
            shiftedValue = 1U << bitsNeeded;
        }
        writeBits(value - minVal, bitsNeeded);
    }

    void BitPacker::writeFloat(float value, float minValue, float maxValue, uint32_t precision)
    {
        value = std::max(value, minValue);
        value = std::min(value, maxValue);

        float const normalized = (value - minValue) / (maxValue - minValue);
        auto quantized = static_cast<uint32_t>(std::lround(normalized * precision));

        quantized = std::min(quantized, precision);

        uint32_t bitsNeeded = 0;
        uint32_t shiftedValue  = 1U << bitsNeeded;
        while ((shiftedValue) <= precision) {
            bitsNeeded++;
            if (shiftedValue > INT32_MAX) {
                break;
            }
            shiftedValue = 1U << bitsNeeded;
        }
        writeBits(quantized, bitsNeeded);
    }


    const std::vector<uint8_t> &BitPacker::getBuffer() const
    {
        return _buffer;
    }

    size_t BitPacker::getByteSize() const
    {
        return (_bitPosition + byteFiller) / byteSize;;
    }

    size_t BitPacker::getBitSize() const
    {
        return _bitPosition;
    }


}// namespace cmn