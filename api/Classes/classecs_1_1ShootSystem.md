---
title: ecs::ShootSystem

---

# ecs::ShootSystem






`#include <ShootSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](Classes/classecs_1_1ShootSystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) override<br>[Shoot]() a project If the player touch the key space a projectile is send.  |
| | **[ShootSystem](Classes/classecs_1_1ShootSystem.md#function-shootsystem)**() =default |

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

[Shoot]() a project If the player touch the key space a projectile is send. 

**Parameters**: 

  * **ecs** 


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


### function ShootSystem

```cpp
ShootSystem() =default
```


-------------------------------

Updated on 2025-12-15 at 10:44:56 +0000