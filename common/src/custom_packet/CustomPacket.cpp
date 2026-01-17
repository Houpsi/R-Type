/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** CustomPacket
*/
#include "CustomPacket.hpp"
#include "lz4.h"
#include <cstring>

namespace cmn {

    const void *CustomPacket::onSend(size_t &size)
    {
        const void* srcData = getData();
        std::size_t const srcSize = getDataSize();

        if (srcSize == 0) {
            size = 0;
            return nullptr;
        }

        int const maxCompressedSize = LZ4_compressBound(static_cast<int>(srcSize));

        _compressedBuffer.resize(maxCompressedSize + sizeof(std::uint32_t));

        auto originalSize = static_cast<std::uint32_t>(srcSize);
        std::memcpy(_compressedBuffer.data(), &originalSize, sizeof(std::uint32_t));

        int const compressedSize = LZ4_compress_default(
            static_cast<const char*>(srcData),
            _compressedBuffer.data() + sizeof(std::uint32_t),
            static_cast<int>(srcSize),
            maxCompressedSize
        );

        if (compressedSize <= 0) {
            size = srcSize;
            return srcData;
        }

        size = compressedSize + sizeof(std::uint32_t);
        return _compressedBuffer.data();
    }

    void CustomPacket::onReceive(const void *data, std::size_t size)
    {
        if (size <= sizeof(std::uint32_t)) {
            return;
        }

        std::uint32_t originalSize = 0;
        std::memcpy(&originalSize, data, sizeof(std::uint32_t));

        _decompressedBuffer.resize(originalSize);

        int const decompressedSize = LZ4_decompress_safe(
            static_cast<const char*>(data) + sizeof(std::uint32_t),
            _decompressedBuffer.data(),
            static_cast<int>(size - sizeof(std::uint32_t)),
            static_cast<int>(originalSize)
        );

        if (decompressedSize < 0) {
            return;
        }

        append(_decompressedBuffer.data(), decompressedSize);
    }
    
}// namespace server