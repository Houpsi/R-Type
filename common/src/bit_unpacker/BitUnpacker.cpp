/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** BitUnpacker
*/

#include "BitUnpacker.hpp"
#include "constants/BitPackingConstants.hpp"

namespace cmn {

    BitUnpacker::BitUnpacker(std::vector<uint8_t> &buffer, size_t size)
        : _buffer(buffer), _bufferSize(size) {}

    uint32_t BitUnpacker::readBits(uint8_t numBits)
    {
        if (numBits == 0 || numBits > maxBits) {
            return 0;
        }

        uint32_t result = 0;
        uint32_t bitsRead = 0;

        while (bitsRead < numBits) {
            size_t const byteIndex = _bitPosition / byteSize;
            size_t const bitOffset = _bitPosition % byteSize;

            if (byteIndex >= _bufferSize) {
                return result;
            }

            uint32_t const bitsAvailable = byteSize - bitOffset;
            uint32_t const bitsToRead = std::min(numBits - bitsRead, bitsAvailable);

            uint32_t const mask = ((1U << bitsToRead) - 1);
            uint32_t const bits = (_buffer[byteIndex] >> bitOffset) & mask;

            result |= (bits << bitsRead);

            bitsRead += bitsToRead;
            _bitPosition += bitsToRead;
        }

        return result;
    }

    bool BitUnpacker::readBool()
    {
        return readBits(1) != 0;
    }

    uint8_t BitUnpacker::readUInt8()
    {
        return readBits(uint8Size);
    }

    uint16_t BitUnpacker::readUInt16()
    {
        return readBits(uint16Size);
    }

    uint32_t BitUnpacker::readUInt32()
    {
        return readBits(uint32Size);
    }

    uint32_t BitUnpacker::readRangedUInt(uint32_t minVal, uint32_t maxVal)
    {
        uint32_t const range = maxVal - minVal;
        uint32_t bitsNeeded = 0;
        uint32_t shiftedValue = 1U << bitsNeeded;

        while ((shiftedValue) <= range) {
            bitsNeeded++;
            if (shiftedValue > INT32_MAX) {
                break;
            }
            shiftedValue = 1U << bitsNeeded;
        }
        return readBits(bitsNeeded) + minVal;
    }

    float BitUnpacker::readFloat(float minValue, float maxValue, uint32_t precision)
    {
        uint32_t bitsNeeded = 0;
        uint32_t shiftedValue = 1U << bitsNeeded;

        while ((shiftedValue) <= precision) {
            bitsNeeded++;
            if (shiftedValue > INT32_MAX) {
                break;
            }
            shiftedValue = 1U << bitsNeeded;
        }

        uint32_t const quantized = readBits(bitsNeeded);
        float const normalized = static_cast<float>(quantized) / static_cast<float>(precision);
        return minValue + (normalized * (maxValue - minValue));
    }


}// namespace cmn