---
title: ecs::System

---

# ecs::System






`#include <System.hpp>`

Inherited by [ecs::BackgroundSystem](Classes/classecs_1_1BackgroundSystem.md), [ecs::CollisionSystem](Classes/classecs_1_1CollisionSystem.md), [ecs::DestroySystem](Classes/classecs_1_1DestroySystem.md), [ecs::DummySystem](Classes/classecs_1_1DummySystem.md), [ecs::HealthSystem](Classes/classecs_1_1HealthSystem.md), [ecs::InputSystem](Classes/classecs_1_1InputSystem.md), [ecs::MovementSystem](Classes/classecs_1_1MovementSystem.md), [ecs::PlayerAnimationSystem](Classes/classecs_1_1PlayerAnimationSystem.md), [ecs::RenderSystem](Classes/classecs_1_1RenderSystem.md), [ecs::ShootSystem](Classes/classecs_1_1ShootSystem.md), [ecs::SoundSystem](Classes/classecs_1_1SoundSystem.md), [ecs::SpriteAnimationSystem](Classes/classecs_1_1SpriteAnimationSystem.md), [ecs::VelocitySystem](Classes/classecs_1_1VelocitySystem.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual | **[~System](Classes/classecs_1_1System.md#function-~system)**() =default |
| virtual void | **[update](Classes/classecs_1_1System.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) =0 |
| | **[System](Classes/classecs_1_1System.md#function-system)**() =default |

## Public Functions Documentation

### function ~System

```cpp
virtual ~System() =default
```


### function update

```cpp
virtual void update(
    EcsManager & ecs
) =0
```


**Reimplemented by**: [ecs::CollisionSystem::update](Classes/classecs_1_1CollisionSystem.md#function-update), [ecs::RenderSystem::update](Classes/classecs_1_1RenderSystem.md#function-update), [ecs::SoundSystem::update](Classes/classecs_1_1SoundSystem.md#function-update), [ecs::BackgroundSystem::update](Classes/classecs_1_1BackgroundSystem.md#function-update), [ecs::DestroySystem::update](Classes/classecs_1_1DestroySystem.md#function-update), [ecs::HealthSystem::update](Classes/classecs_1_1HealthSystem.md#function-update), [ecs::InputSystem::update](Classes/classecs_1_1InputSystem.md#function-update), [ecs::MovementSystem::update](Classes/classecs_1_1MovementSystem.md#function-update), [ecs::PlayerAnimationSystem::update](Classes/classecs_1_1PlayerAnimationSystem.md#function-update), [ecs::ShootSystem::update](Classes/classecs_1_1ShootSystem.md#function-update), [ecs::SpriteAnimationSystem::update](Classes/classecs_1_1SpriteAnimationSystem.md#function-update), [ecs::VelocitySystem::update](Classes/classecs_1_1VelocitySystem.md#function-update), [ecs::DummySystem::update](Classes/classecs_1_1DummySystem.md#function-update)


### function System

```cpp
System() =default
```


-------------------------------

Updated on 2026-01-17 at 14:46:01 +0000