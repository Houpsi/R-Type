---
title: ecs::Position

---

# ecs::Position






`#include <Position.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Position](Classes/classecs_1_1Position.md#function-~position)**() override =default |
| void | **[setY](Classes/classecs_1_1Position.md#function-sety)**(float y) |
| void | **[setX](Classes/classecs_1_1Position.md#function-setx)**(float x) |
| float | **[getY](Classes/classecs_1_1Position.md#function-gety)**() const |
| float | **[getX](Classes/classecs_1_1Position.md#function-getx)**() const |
| | **[Position](Classes/classecs_1_1Position.md#function-position)**(float x, float y) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~Position

```cpp
~Position() override =default
```


### function setY

```cpp
void setY(
    float y
)
```


### function setX

```cpp
void setX(
    float x
)
```


### function getY

```cpp
float getY() const
```


### function getX

```cpp
float getX() const
```


### function Position

```cpp
inline explicit Position(
    float x,
    float y
)
```


-------------------------------

Updated on 2026-01-13 at 15:10:47 +0000