---
title: ecs::CollisionSystem

---

# ecs::CollisionSystem






`#include <CollisionSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](Classes/classecs_1_1CollisionSystem.md#function-update)**([ecs::EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) override |
| | **[CollisionSystem](Classes/classecs_1_1CollisionSystem.md#function-collisionsystem)**() =default |

## Additional inherited members

**Public Functions inherited from [ecs::System](Classes/classecs_1_1System.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~System](Classes/classecs_1_1System.md#function-~system)**() =default |
| | **[System](Classes/classecs_1_1System.md#function-system)**() =default |


## Public Functions Documentation

### function update

```cpp
virtual void update(
    ecs::EcsManager & ecs
) override
```


**Parameters**: 

  * **ecs** 


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


Check if the entity can have a collision, and is there is one check if there is a collision with another entity 


### function CollisionSystem

```cpp
CollisionSystem() =default
```


-------------------------------

Updated on 2026-01-18 at 20:39:22 +0000