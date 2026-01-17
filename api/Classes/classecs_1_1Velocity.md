---
title: ecs::Velocity

---

# ecs::Velocity



 [More...](#detailed-description)


`#include <Velocity.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Velocity](Classes/classecs_1_1Velocity.md#function-~velocity)**() override =default |
| void | **[setVelocity](Classes/classecs_1_1Velocity.md#function-setvelocity)**(float velocity) |
| void | **[setDirection](Classes/classecs_1_1Velocity.md#function-setdirection)**(std::pair< float, float > direction) |
| float | **[getVelocity](Classes/classecs_1_1Velocity.md#function-getvelocity)**() const |
| std::pair< float, float > | **[getDirection](Classes/classecs_1_1Velocity.md#function-getdirection)**() const |
| | **[Velocity](Classes/classecs_1_1Velocity.md#function-velocity)**(float velocity, std::pair< float, float > direction) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Detailed Description

```cpp
class ecs::Velocity;
```


function of the speed and the direction 

## Public Functions Documentation

### function ~Velocity

```cpp
~Velocity() override =default
```


### function setVelocity

```cpp
void setVelocity(
    float velocity
)
```


### function setDirection

```cpp
void setDirection(
    std::pair< float, float > direction
)
```


### function getVelocity

```cpp
float getVelocity() const
```


### function getDirection

```cpp
std::pair< float, float > getDirection() const
```


### function Velocity

```cpp
inline explicit Velocity(
    float velocity,
    std::pair< float, float > direction
)
```


-------------------------------

Updated on 2026-01-17 at 23:36:19 +0000