---
title: ecs::RenderSystem

---

# ecs::RenderSystem






`#include <RenderSystem.hpp>`

Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](Classes/classecs_1_1RenderSystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & ecs) |
| | **[RenderSystem](Classes/classecs_1_1RenderSystem.md#function-rendersystem)**(sf::RenderWindow & window, const std::string & nameShader) |

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
)
```


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


### function RenderSystem

```cpp
explicit RenderSystem(
    sf::RenderWindow & window,
    const std::string & nameShader
)
```


-------------------------------

Updated on 2026-01-18 at 00:13:20 +0000