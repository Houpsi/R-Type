---
title: ecs::Background
summary: A component handling background logic, specifically for scrolling/looping effects. 

---

# ecs::Background



A component handling background logic, specifically for scrolling/looping effects. 


`#include <Background.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Background](Classes/classecs_1_1Background.md#function-~background)**() override =default |
| float | **[getWidth](Classes/classecs_1_1Background.md#function-getwidth)**() const |
| bool | **[getIsLooping](Classes/classecs_1_1Background.md#function-getislooping)**() const |
| | **[Background](Classes/classecs_1_1Background.md#function-background)**(float witdh)<br>Construct a new [Background](Classes/classecs_1_1Background.md) object.  |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~Background

```cpp
~Background() override =default
```


### function getWidth

```cpp
float getWidth() const
```


### function getIsLooping

```cpp
bool getIsLooping() const
```


### function Background

```cpp
inline explicit Background(
    float witdh
)
```

Construct a new [Background](Classes/classecs_1_1Background.md) object. 

**Parameters**: 

  * **width** The width of the sprite/texture used for the background. This defines the point at which the background should loop. 


-------------------------------

Updated on 2026-01-18 at 11:25:11 +0000