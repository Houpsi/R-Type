---
title: ecs::AABB

---

# ecs::AABB






`#include <CollisionSystem.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[intersects](Classes/classecs_1_1AABB.md#function-intersects)**(const [AABB](Classes/classecs_1_1AABB.md) & other) const |
| bool | **[contains](Classes/classecs_1_1AABB.md#function-contains)**(const [AABB](Classes/classecs_1_1AABB.md) & other) const |
| | **[AABB](Classes/classecs_1_1AABB.md#function-aabb)**() |
| | **[AABB](Classes/classecs_1_1AABB.md#function-aabb)**(float x, float y, float w, float h) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| float | **[y](Classes/classecs_1_1AABB.md#variable-y)**  |
| float | **[x](Classes/classecs_1_1AABB.md#variable-x)**  |
| float | **[width](Classes/classecs_1_1AABB.md#variable-width)**  |
| float | **[height](Classes/classecs_1_1AABB.md#variable-height)**  |

## Public Functions Documentation

### function intersects

```cpp
inline bool intersects(
    const AABB & other
) const
```


### function contains

```cpp
inline bool contains(
    const AABB & other
) const
```


### function AABB

```cpp
inline AABB()
```


### function AABB

```cpp
inline AABB(
    float x,
    float y,
    float w,
    float h
)
```


## Public Attributes Documentation

### variable y

```cpp
float y;
```


### variable x

```cpp
float x;
```


### variable width

```cpp
float width;
```


### variable height

```cpp
float height;
```


-------------------------------

Updated on 2026-01-16 at 18:45:29 +0000