---
title: ecs::Shoot

---

# ecs::Shoot



 [More...](#detailed-description)


`#include <Shoot.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Shoot](Classes/classecs_1_1Shoot.md#function-~shoot)**() override =default |
| void | **[setTimeSinceLastShot](Classes/classecs_1_1Shoot.md#function-settimesincelastshot)**(float t)<br>Sets the last shot.  |
| void | **[setDamage](Classes/classecs_1_1Shoot.md#function-setdamage)**(int damage)<br>Sets the shoot damage.  |
| void | **[setCooldown](Classes/classecs_1_1Shoot.md#function-setcooldown)**(float cooldown)<br>Sets the shoot cooldown.  |
| float | **[getTimeSinceLastShot](Classes/classecs_1_1Shoot.md#function-gettimesincelastshot)**() const<br>Gets the last shot.  |
| int | **[getDamage](Classes/classecs_1_1Shoot.md#function-getdamage)**() const<br>Gets the shoot damage.  |
| float | **[getCooldown](Classes/classecs_1_1Shoot.md#function-getcooldown)**() const<br>Gets the shoot cooldown.  |
| | **[Shoot](Classes/classecs_1_1Shoot.md#function-shoot)**(int damage, float cooldown) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Detailed Description

```cpp
class ecs::Shoot;
```


damage and cooldown 

## Public Functions Documentation

### function ~Shoot

```cpp
~Shoot() override =default
```


### function setTimeSinceLastShot

```cpp
void setTimeSinceLastShot(
    float t
)
```

Sets the last shot. 

**Parameters**: 

  * **t** New shot of the shoot 


### function setDamage

```cpp
void setDamage(
    int damage
)
```

Sets the shoot damage. 

**Parameters**: 

  * **damage** New damage of the shoot 


### function setCooldown

```cpp
void setCooldown(
    float cooldown
)
```

Sets the shoot cooldown. 

**Parameters**: 

  * **cooldown** New cooldown of the shoot 


### function getTimeSinceLastShot

```cpp
float getTimeSinceLastShot() const
```

Gets the last shot. 

**Return**: The last shot 

### function getDamage

```cpp
int getDamage() const
```

Gets the shoot damage. 

**Return**: The damage of the shoot 

### function getCooldown

```cpp
float getCooldown() const
```

Gets the shoot cooldown. 

**Return**: The cooldown of the shoot 

### function Shoot

```cpp
inline explicit Shoot(
    int damage,
    float cooldown
)
```


-------------------------------

Updated on 2026-01-13 at 15:10:47 +0000