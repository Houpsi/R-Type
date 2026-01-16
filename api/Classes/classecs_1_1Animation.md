---
title: ecs::Animation

---

# ecs::Animation






`#include <Animation.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[updateAnimation](Classes/classecs_1_1Animation.md#function-updateanimation)**(float dt) |
| void | **[setAnimTimer](Classes/classecs_1_1Animation.md#function-setanimtimer)**(const float animTimer) |
| void | **[setAnimFrame](Classes/classecs_1_1Animation.md#function-setanimframe)**(const int animFrame) |
| std::pair< int, int > | **[getSpriteSize](Classes/classecs_1_1Animation.md#function-getspritesize)**() |
| int | **[getOffsetX](Classes/classecs_1_1Animation.md#function-getoffsetx)**() const |
| int | **[getNumberFrame](Classes/classecs_1_1Animation.md#function-getnumberframe)**() const |
| float | **[getAnimTimer](Classes/classecs_1_1Animation.md#function-getanimtimer)**() const |
| float | **[getAnimSpeed](Classes/classecs_1_1Animation.md#function-getanimspeed)**() const |
| int | **[getAnimFrame](Classes/classecs_1_1Animation.md#function-getanimframe)**() const |
| | **[Animation](Classes/classecs_1_1Animation.md#function-animation)**(const std::pair< int, int > size, const int offsetX, const int numberFrame) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function updateAnimation

```cpp
void updateAnimation(
    float dt
)
```


### function setAnimTimer

```cpp
void setAnimTimer(
    const float animTimer
)
```


### function setAnimFrame

```cpp
void setAnimFrame(
    const int animFrame
)
```


### function getSpriteSize

```cpp
std::pair< int, int > getSpriteSize()
```


### function getOffsetX

```cpp
int getOffsetX() const
```


### function getNumberFrame

```cpp
int getNumberFrame() const
```


### function getAnimTimer

```cpp
float getAnimTimer() const
```


### function getAnimSpeed

```cpp
float getAnimSpeed() const
```


### function getAnimFrame

```cpp
int getAnimFrame() const
```


### function Animation

```cpp
inline explicit Animation(
    const std::pair< int, int > size,
    const int offsetX,
    const int numberFrame
)
```


-------------------------------

Updated on 2026-01-16 at 16:50:30 +0000