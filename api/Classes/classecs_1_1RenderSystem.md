---
title: ecs::RenderSystem

---

# ecs::RenderSystem






`#include <RenderSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~RenderSystem](Classes/classecs_1_1RenderSystem.md#function-~rendersystem)**() override =default |
| virtual void | **[update](Classes/classecs_1_1RenderSystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) override |
| | **[RenderSystem](Classes/classecs_1_1RenderSystem.md#function-rendersystem)**(sf::RenderWindow & window) |

## Additional inherited members

**Public Functions inherited from [ecs::System](Classes/classecs_1_1System.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~System](Classes/classecs_1_1System.md#function-~system)**() =default |
| | **[System](Classes/classecs_1_1System.md#function-system)**() =default |


## Public Functions Documentation

### function ~RenderSystem

```cpp
~RenderSystem() override =default
```


### function update

```cpp
virtual void update(
    EcsManager & ecs
) override
```


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


### function RenderSystem

```cpp
inline explicit RenderSystem(
    sf::RenderWindow & window
)
```


-------------------------------

Updated on 2025-12-15 at 10:44:56 +0000