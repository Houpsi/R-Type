/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** TestsCollision
*/

#include "components/Collision.hpp"
#include <gtest/gtest.h>

namespace ecs
{
	TEST(CollisionTest, ConstructorInitializesValues) {
		Collision col(TypeCollision::PLAYER, 50.f, 30.f);

		EXPECT_EQ(col.getTypeCollision(), TypeCollision::PLAYER);
		EXPECT_FLOAT_EQ(col.getHeight(), 50.f);
		EXPECT_FLOAT_EQ(col.getWidth(), 30.f);
		EXPECT_FALSE(col.getIsTrigger());
	}

	TEST(CollisionTest, SettersUpdateValues) {
		Collision col(TypeCollision::ENEMY, 10.f, 10.f);

		col.setTypeCollision(TypeCollision::PLAYER_PROJECTILE);
		col.setHeight(42.f);
		col.setWidth(21.f);
		col.setIsTrigger(true);

		EXPECT_EQ(col.getTypeCollision(), TypeCollision::PLAYER_PROJECTILE);
		EXPECT_FLOAT_EQ(col.getHeight(), 42.f);
		EXPECT_FLOAT_EQ(col.getWidth(), 21.f);
		EXPECT_TRUE(col.getIsTrigger());
	}

	TEST(CollisionTest, TriggerCanBeEnabledAndDisabled) {
		Collision col(TypeCollision::OBSTACLE, 100.f, 100.f);

		EXPECT_FALSE(col.getIsTrigger());
		col.setIsTrigger(true);
		EXPECT_TRUE(col.getIsTrigger());
		col.setIsTrigger(false);
		EXPECT_FALSE(col.getIsTrigger());
	}

	TEST(CollisionTest, TypeCollisionCanChange) {
		Collision col(TypeCollision::PLAYER, 20.f, 20.f);

		col.setTypeCollision(TypeCollision::ENEMY_PROJECTILE);
		EXPECT_EQ(col.getTypeCollision(), TypeCollision::ENEMY_PROJECTILE);

		col.setTypeCollision(TypeCollision::OBSTACLE);
		EXPECT_EQ(col.getTypeCollision(), TypeCollision::OBSTACLE);
	}

	TEST(CollisionTest, SizeValuesUpdateCorrectly) {
		Collision col(TypeCollision::ENEMY, 5.f, 5.f);

		col.setHeight(250.f);
		col.setWidth(125.f);

		EXPECT_FLOAT_EQ(col.getHeight(), 250.f);
		EXPECT_FLOAT_EQ(col.getWidth(), 125.f);
	}
}