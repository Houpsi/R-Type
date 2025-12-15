/*
** EPITECH PROJECT, 2025
** ECSLib
** File description:
** TestsSprite
*/
#include <gtest/gtest.h>

#include "components/Sprite.hpp"

namespace ecs {
//    TEST(SpriteTest, ConstructorLoadsTextureAndSpriteIsValid)
//    {
//        std::string path = "assets/image.png";
//
//        Sprite sprite(path);
//        const sf::Sprite &spr = sprite.getSprite();
//
//        ASSERT_NE(spr.getTexture(), nullptr);
//
//        sf::Vector2u size = spr.getTexture().getSize();
//        EXPECT_GT(size.x, 0);
//        EXPECT_GT(size.y, 0);
//    }

    TEST(SpriteTest, GetSpriteReturnsReference)
    {
        sf::Vector2f scale(2.0f, 2.0f);
        sf::Texture texture("assets/textureError.png");
        Sprite sprite(texture, scale);

        const sf::Sprite &spr1 = sprite.getSprite();
        const sf::Sprite &spr2 = sprite.getSprite();

        ASSERT_EQ(&spr1, &spr2);
    }

//    TEST(SpriteTest, InvalidTextureDoesNotCrash)
//    {
//        sf::Vector2f scale(2.0f, 2.0f);
//        sf::Texture texture("nope/not_found.png");
//        ASSERT_NO_THROW(Sprite sprite(texture, scale));
//    }
}
