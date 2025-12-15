---
title: ecs

---

# ecs



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[ecs::VelocitySystem](Classes/classecs_1_1VelocitySystem.md)**  |
| class | **[ecs::Velocity](Classes/classecs_1_1Velocity.md)**  |
| class | **[ecs::System](Classes/classecs_1_1System.md)**  |
| class | **[ecs::SpriteAnimationSystem](Classes/classecs_1_1SpriteAnimationSystem.md)**  |
| class | **[ecs::Sprite](Classes/classecs_1_1Sprite.md)**  |
| class | **[ecs::Sound](Classes/classecs_1_1Sound.md)**  |
| class | **[ecs::ShootSystem](Classes/classecs_1_1ShootSystem.md)**  |
| class | **[ecs::Shoot](Classes/classecs_1_1Shoot.md)**  |
| class | **[ecs::ResourceManager](Classes/classecs_1_1ResourceManager.md)**  |
| class | **[ecs::RenderSystem](Classes/classecs_1_1RenderSystem.md)**  |
| class | **[ecs::Position](Classes/classecs_1_1Position.md)**  |
| class | **[ecs::PlayerAnimationSystem](Classes/classecs_1_1PlayerAnimationSystem.md)**  |
| class | **[ecs::PlayerAnimation](Classes/classecs_1_1PlayerAnimation.md)**  |
| class | **[ecs::MovementSystem](Classes/classecs_1_1MovementSystem.md)**  |
| class | **[ecs::InputSystem](Classes/classecs_1_1InputSystem.md)**  |
| class | **[ecs::InputPlayer](Classes/classecs_1_1InputPlayer.md)**  |
| class | **[ecs::HealthSystem](Classes/classecs_1_1HealthSystem.md)**  |
| class | **[ecs::Health](Classes/classecs_1_1Health.md)**  |
| class | **[ecs::Entity](Classes/classecs_1_1Entity.md)**  |
| class | **[ecs::Enemy](Classes/classecs_1_1Enemy.md)**  |
| class | **[ecs::EcsManager](Classes/classecs_1_1EcsManager.md)**  |
| class | **[ecs::DummySystem](Classes/classecs_1_1DummySystem.md)**  |
| class | **[ecs::DummyComponent](Classes/classecs_1_1DummyComponent.md)**  |
| class | **[ecs::DestroySystem](Classes/classecs_1_1DestroySystem.md)**  |
| class | **[ecs::Destroy](Classes/classecs_1_1Destroy.md)**  |
| class | **[ecs::Component](Classes/classecs_1_1Component.md)**  |
| class | **[ecs::CollisionSystem](Classes/classecs_1_1CollisionSystem.md)**  |
| class | **[ecs::Collision](Classes/classecs_1_1Collision.md)**  |
| class | **[ecs::BackgroundSystem](Classes/classecs_1_1BackgroundSystem.md)** <br>[System](Classes/classecs_1_1System.md) responsible for the infinite scrolling logic of the background.  |
| class | **[ecs::Background](Classes/classecs_1_1Background.md)** <br>A component handling background logic, specifically for scrolling/looping effects.  |
| class | **[ecs::Animation](Classes/classecs_1_1Animation.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| enum| **[TypeCollision](Namespaces/namespaceecs.md#enum-typecollision)** { PLAYER_PROJECTILE, PLAYER, OBSTACLE, ENEMY_PROJECTILE, ENEMY} |

## Functions

|                | Name           |
| -------------- | -------------- |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , CreateEntityIncreasesSize ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , DeltaTimeSetAndGetWorks ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , AddSystemStoresSystem ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , UpdateSystemsCallsUpdate ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetEntitiesWithComponentWorks ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetNegHealth ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , GetPosition ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(EcsManagerTest , SetPosition ) |
| | **[TEST](Namespaces/namespaceecs.md#function-test)**(SpriteTest , GetSpriteReturnsReference ) |

## Types Documentation

### enum TypeCollision

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| PLAYER_PROJECTILE | |   |
| PLAYER | |   |
| OBSTACLE | |   |
| ENEMY_PROJECTILE | |   |
| ENEMY | |   |





## Functions Documentation

### function TEST

```cpp
TEST(
    EcsManagerTest ,
    CreateEntityIncreasesSize 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    DeltaTimeSetAndGetWorks 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    AddSystemStoresSystem 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    UpdateSystemsCallsUpdate 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetEntitiesWithComponentWorks 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetNegHealth 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    GetPosition 
)
```


### function TEST

```cpp
TEST(
    EcsManagerTest ,
    SetPosition 
)
```


### function TEST

```cpp
TEST(
    SpriteTest ,
    GetSpriteReturnsReference 
)
```






-------------------------------

Updated on 2025-12-15 at 10:44:19 +0000