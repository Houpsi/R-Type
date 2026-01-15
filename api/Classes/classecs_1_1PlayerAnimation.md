---
title: ecs::PlayerAnimation

---

# ecs::PlayerAnimation






`#include <PlayerAnimation.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~PlayerAnimation](Classes/classecs_1_1PlayerAnimation.md#function-~playeranimation)**() override =default |
| void | **[updateAnimation](Classes/classecs_1_1PlayerAnimation.md#function-updateanimation)**(float dt, const bool isDown, const bool isUp) |
| std::size_t | **[getId](Classes/classecs_1_1PlayerAnimation.md#function-getid)**() const |
| int | **[getAnimFrame](Classes/classecs_1_1PlayerAnimation.md#function-getanimframe)**() const |
| | **[PlayerAnimation](Classes/classecs_1_1PlayerAnimation.md#function-playeranimation)**() |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~PlayerAnimation

```cpp
~PlayerAnimation() override =default
```


### function updateAnimation

```cpp
void updateAnimation(
    float dt,
    const bool isDown,
    const bool isUp
)
```


### function getId

```cpp
std::size_t getId() const
```


### function getAnimFrame

```cpp
int getAnimFrame() const
```


### function PlayerAnimation

```cpp
PlayerAnimation()
```


-------------------------------

Updated on 2026-01-15 at 18:57:40 +0000