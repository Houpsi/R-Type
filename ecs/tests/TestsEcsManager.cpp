/*
** EPITECH PROJECT, 2025
** Test EcsManager
** File description:
** Test
*/

#include <gtest/gtest.h>

#include "EcsManager.hpp"
#include "System.hpp"

class DummySystem : public System {
public:
    bool updated = false;

    void update(EcsManager& manager) override {
        updated = true;
    }
};

TEST(EcsManagerTest, CreateEntityIncreasesSize) {
    EcsManager manager;

    auto e1 = manager.createEntity();
    auto e2 = manager.createEntity();

    EXPECT_EQ(manager.getEntities().size(), 2);
}

TEST(EcsManagerTest, DeltaTimeSetAndGetWorks) {
    EcsManager manager;

    manager.setDeltaTime(0.16f);
    EXPECT_FLOAT_EQ(manager.deltaTime(), 0.16f);
}

TEST(EcsManagerTest, AddSystemStoresSystem) {
    EcsManager manager;

    auto sys = manager.addSystem<DummySystem>();

    EXPECT_EQ(manager.getEntities().size(), 0);
    EXPECT_FALSE(sys->updated);
}

TEST(EcsManagerTest, UpdateSystemsCallsUpdate) {
    EcsManager manager;

    auto sys = manager.addSystem<DummySystem>();

    manager.updateSystems();

    EXPECT_TRUE(sys->updated);
}

class DummyComponent : public Component {
public:
    int value = 0;
};

TEST(EcsManagerTest, GetEntitiesWithComponentWorks) {
    EcsManager manager;

    auto entity1 = manager.createEntity();
    auto entity2 = manager.createEntity();

    entity1->addComponent<DummyComponent>();

    auto entitiesWithDummy = manager.getEntitiesWithComponent<DummyComponent>();
    EXPECT_EQ(entitiesWithDummy.size(), 1);
}

