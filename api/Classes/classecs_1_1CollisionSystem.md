---
title: ecs::CollisionSystem

---

# ecs::CollisionSystem






`#include <CollisionSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](Classes/classecs_1_1CollisionSystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) override |
| bool | **[shouldIgnoreCollision](Classes/classecs_1_1CollisionSystem.md#function-shouldignorecollision)**([TypeCollision](Namespaces/namespaceecs.md#enum-typecollision) a, [TypeCollision](Namespaces/namespaceecs.md#enum-typecollision) b) |
| bool | **[isColliding](Classes/classecs_1_1CollisionSystem.md#function-iscolliding)**(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) |
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
    EcsManager & ecs
) override
```


**Parameters**: 

  * **ecs** 


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


Check if the entity can have a collision, and is there is one check if there is a collision with another entity 


### function shouldIgnoreCollision

```cpp
static bool shouldIgnoreCollision(
    TypeCollision a,
    TypeCollision b
)
```


### function isColliding

```cpp
static bool isColliding(
    float x1,
    float y1,
    float w1,
    float h1,
    float x2,
    float y2,
    float w2,
    float h2
)
```


### function CollisionSystem

```cpp
CollisionSystem() =default
```


-------------------------------

Updated on 2025-12-15 at 09:02:05 +0000