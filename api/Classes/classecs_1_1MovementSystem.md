---
title: ecs::MovementSystem

---

# ecs::MovementSystem






`#include <MovementSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~MovementSystem](Classes/classecs_1_1MovementSystem.md#function-~movementsystem)**() override =default |
| virtual void | **[update](Classes/classecs_1_1MovementSystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) override |
| | **[MovementSystem](Classes/classecs_1_1MovementSystem.md#function-movementsystem)**() |

## Additional inherited members

**Public Functions inherited from [ecs::System](Classes/classecs_1_1System.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~System](Classes/classecs_1_1System.md#function-~system)**() =default |
| | **[System](Classes/classecs_1_1System.md#function-system)**() =default |


## Public Functions Documentation

### function ~MovementSystem

```cpp
~MovementSystem() override =default
```


### function update

```cpp
virtual void update(
    EcsManager & ecs
) override
```


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


### function MovementSystem

```cpp
inline explicit MovementSystem()
```


-------------------------------

Updated on 2025-12-15 at 10:44:56 +0000