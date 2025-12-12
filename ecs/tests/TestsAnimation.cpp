/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** TestsAnimation
*/
#include "components/Animation.hpp"
#include <gtest/gtest.h>

namespace ecs
{
	TEST(AnimationTest, ConstructorValuesAreCorrect) {
		Animation anim({64, 64}, 32, 5);

		EXPECT_EQ(anim.getSpriteSize().first, 64);
		EXPECT_EQ(anim.getSpriteSize().second, 64);
		EXPECT_EQ(anim.getOffsetX(), 32);
		EXPECT_EQ(anim.getNumberFrame(), 5);

		EXPECT_EQ(anim.getAnimFrame(), 0);
		EXPECT_FLOAT_EQ(anim.getAnimTimer(), 0.f);
		EXPECT_FLOAT_EQ(anim.getAnimSpeed(), 0.1f);
	}

	TEST(AnimationTest, SetterGetterWork) {
		Animation anim({64, 64}, 32, 3);

		anim.setAnimFrame(2);
		anim.setAnimTimer(0.5f);

		EXPECT_EQ(anim.getAnimFrame(), 2);
		EXPECT_FLOAT_EQ(anim.getAnimTimer(), 0.5f);
	}

	TEST(AnimationTest, UpdateAnimationDoesNotAdvanceFrameTooEarly) {
		Animation anim({64, 64}, 32, 4);

		float dt = 0.05f;
		anim.updateAnimation(dt);

		EXPECT_FLOAT_EQ(anim.getAnimTimer(), 0.05f);
		EXPECT_EQ(anim.getAnimFrame(), 0);
	}

	TEST(AnimationTest, UpdateAnimationAdvancesFrameAtCorrectSpeed) {
		Animation anim({64, 64}, 32, 4);

		anim.updateAnimation(0.05f);
		anim.updateAnimation(0.05f);

		EXPECT_EQ(anim.getAnimFrame(), 1);
		EXPECT_FLOAT_EQ(anim.getAnimTimer(), 0.f);
	}

	TEST(AnimationTest, AnimationLoopsAfterLastFrame) {
		Animation anim({64, 64}, 32, 3);

		anim.setAnimFrame(2);
		anim.updateAnimation(0.1f);

		EXPECT_EQ(anim.getAnimFrame(), 0);
	}
}
