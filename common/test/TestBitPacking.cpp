/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** TestBitPacking
*/

#include <gtest//gtest.h>
#include "bit_packer/BitPacker.hpp"
#include "bit_unpacker/BitUnpacker.hpp"

namespace cmn {

    TEST(BitPackingTest, WriteAndReadBool)
    {
        BitPacker packer;
        packer.writeBool(true);
        packer.writeBool(false);
        packer.writeBool(true);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_TRUE(unpacker.readBool());
        EXPECT_FALSE(unpacker.readBool());
        EXPECT_TRUE(unpacker.readBool());
    }

    TEST(BitPackingTest, WriteAndReadUInt8)
    {
        BitPacker packer;
        packer.writeUInt8(42);
        packer.writeUInt8(255);
        packer.writeUInt8(0);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readUInt8(), 42);
        EXPECT_EQ(unpacker.readUInt8(), 255);
        EXPECT_EQ(unpacker.readUInt8(), 0);
    }

    TEST(BitPackingTest, WriteAndReadUInt16)
    {
        BitPacker packer;
        packer.writeUInt16(1000);
        packer.writeUInt16(65535);
        packer.writeUInt16(0);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readUInt16(), 1000);
        EXPECT_EQ(unpacker.readUInt16(), 65535);
        EXPECT_EQ(unpacker.readUInt16(), 0);
    }

    TEST(BitPackingTest, WriteAndReadUInt32)
    {
        BitPacker packer;
        packer.writeUInt32(123456);
        packer.writeUInt32(4294967295);
        packer.writeUInt32(0);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readUInt32(), 123456);
        EXPECT_EQ(unpacker.readUInt32(), 4294967295);
        EXPECT_EQ(unpacker.readUInt32(), 0);
    }

    TEST(BitPackingTest, WriteAndReadRangedUInt)
    {
        BitPacker packer;
        packer.writeRangedUInt(50, 0, 100);
        packer.writeRangedUInt(0, 0, 100);
        packer.writeRangedUInt(100, 0, 100);

        packer.writeRangedUInt(7, 0, 15);
        packer.writeRangedUInt(15, 0, 15);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readRangedUInt(0, 100), 50);
        EXPECT_EQ(unpacker.readRangedUInt(0, 100), 0);
        EXPECT_EQ(unpacker.readRangedUInt(0, 100), 100);
        EXPECT_EQ(unpacker.readRangedUInt(0, 15), 7);
        EXPECT_EQ(unpacker.readRangedUInt(0, 15), 15);
    }

    TEST(BitPackingTest, WriteAndReadFloat)
    {
        BitPacker packer;
        packer.writeFloat(25.23f, 0.0f, 100.0f, 10000);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        float result = unpacker.readFloat(0.0f, 100.0f, 10000);
        EXPECT_NEAR(result, 25.23f, 0.01f);
    }

    TEST(BitPackingTest, WriteAndReadFloatWithDifferentPrecisions)
    {
        {
            BitPacker packer;
            packer.writeFloat(25.6f, 0.0f, 100.0f, 1000);

            std::vector<uint8_t> buffer = packer.getBuffer();
            BitUnpacker unpacker(buffer, packer.getByteSize());

            float result = unpacker.readFloat(0.0f, 100.0f, 1000);
            EXPECT_NEAR(result, 25.6f, 0.1f);
        }

        {
            BitPacker packer;
            packer.writeFloat(25.123f, 0.0f, 100.0f, 100000);

            std::vector<uint8_t> buffer = packer.getBuffer();
            BitUnpacker unpacker(buffer, packer.getByteSize());

            float result = unpacker.readFloat(0.0f, 100.0f, 100000);
            EXPECT_NEAR(result, 25.123f, 0.001f);
        }
    }

    TEST(BitPackingTest, WriteAndReadCustomBits)
    {
        BitPacker packer;
        packer.writeBits(5, 3);
        packer.writeBits(7, 3);
        packer.writeBits(0, 3);

        packer.writeBits(3, 2);
        packer.writeBits(1, 2);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readBits(3), 5);
        EXPECT_EQ(unpacker.readBits(3), 7);
        EXPECT_EQ(unpacker.readBits(3), 0);
        EXPECT_EQ(unpacker.readBits(2), 3);
        EXPECT_EQ(unpacker.readBits(2), 1);
    }

    TEST(BitPackingTest, MixedDataTypes)
    {
        BitPacker packer;
        packer.writeBool(true);
        packer.writeUInt8(42);
        packer.writeRangedUInt(50, 0, 100);
        packer.writeUInt16(1000);
        packer.writeBool(false);
        packer.writeBits(3, 2);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_TRUE(unpacker.readBool());
        EXPECT_EQ(unpacker.readUInt8(), 42);
        EXPECT_EQ(unpacker.readRangedUInt(0, 100), 50);
        EXPECT_EQ(unpacker.readUInt16(), 1000);
        EXPECT_FALSE(unpacker.readBool());
        EXPECT_EQ(unpacker.readBits(2), 3);
    }

    TEST(BitPackingTest, CompressionEfficiency)
    {
        BitPacker packer;

        packer.writeBool(true);
        packer.writeBool(false);
        packer.writeBool(true);
        packer.writeBool(true);

        EXPECT_LE(packer.getByteSize(), 1);

        packer.writeRangedUInt(75, 0, 100);

        EXPECT_LE(packer.getByteSize(), 2);
    }

    TEST(BitPackingTest, GameStateExample)
    {
        BitPacker packer;

        packer.writeRangedUInt(8, 0, 255);
        packer.writeBool(true);
        packer.writeRangedUInt(85, 0, 100);
        packer.writeRangedUInt(3, 0, 3);
        packer.writeBits(2, 2);

        EXPECT_LE(packer.getByteSize(), 3);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readRangedUInt(0, 255), 8);
        EXPECT_TRUE(unpacker.readBool());
        EXPECT_EQ(unpacker.readRangedUInt(0, 100), 85);
        EXPECT_EQ(unpacker.readRangedUInt(0, 3), 3);
        EXPECT_EQ(unpacker.readBits(2), 2);
    }

    TEST(BitPackingTest, EdgeCaseMaxValues)
    {
        BitPacker packer;
        packer.writeUInt8(255);
        packer.writeUInt16(65535);
        packer.writeUInt32(4294967295);
        packer.writeRangedUInt(4294967295, 0, 4294967295);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readUInt8(), 255);
        EXPECT_EQ(unpacker.readUInt16(), 65535);
        EXPECT_EQ(unpacker.readUInt32(), 4294967295);
        EXPECT_EQ(unpacker.readRangedUInt(0, 4294967295), 4294967295);
    }

    TEST(BitPackingTest, EdgeCaseMinValues)
    {
        BitPacker packer;
        packer.writeRangedUInt(0, 0, 255);
        packer.writeRangedUInt(0, 0, 65535);
        packer.writeRangedUInt(0, 0, 4294967295);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        EXPECT_EQ(unpacker.readRangedUInt(0, 255), 0);
        EXPECT_EQ(unpacker.readRangedUInt(0, 65535), 0);
        EXPECT_EQ(unpacker.readRangedUInt(0, 4294967295), 0);
    }

    TEST(BitPackingTest, MultipleBooleansEfficiency)
    {
        BitPacker packer;

        for (int i = 0; i < 16; i++) {
            packer.writeBool(i % 2 == 0);
        }

        EXPECT_EQ(packer.getByteSize(), 2);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        for (int i = 0; i < 16; i++) {
            EXPECT_EQ(unpacker.readBool(), i % 2 == 0);
        }
    }

    TEST(BitPackingTest, SequentialReadsAndWrites)
    {
        BitPacker packer;

        for (uint32_t i = 0; i < 10; i++) {
            packer.writeRangedUInt(i, 0, 15);
        }

        EXPECT_EQ(packer.getByteSize(), 5);

        std::vector<uint8_t> buffer = packer.getBuffer();
        BitUnpacker unpacker(buffer, packer.getByteSize());

        for (uint32_t i = 0; i < 10; i++) {
            EXPECT_EQ(unpacker.readRangedUInt(0, 15), i);
        }
    }

}
