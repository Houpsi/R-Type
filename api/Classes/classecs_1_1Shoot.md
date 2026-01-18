---
title: ecs::Shoot

---

# ecs::Shoot



 [More...](#detailed-description)


`#include <Shoot.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[ShootingType](Classes/classecs_1_1Shoot.md#enum-shootingtype)** { Shotgun, Normal, Gatling} |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Shoot](Classes/classecs_1_1Shoot.md#function-~shoot)**() override =default |
| void | **[updateShootingType](Classes/classecs_1_1Shoot.md#function-updateshootingtype)**() |
| void | **[setTimeSinceLastShot](Classes/classecs_1_1Shoot.md#function-settimesincelastshot)**(float t)<br>Sets the last shot.  |
| void | **[setShootTimer](Classes/classecs_1_1Shoot.md#function-setshoottimer)**(float cooldown)<br>Sets the shooter.  |
| void | **[setDamage](Classes/classecs_1_1Shoot.md#function-setdamage)**(int damage)<br>Sets the shoot damage.  |
| void | **[setCooldown](Classes/classecs_1_1Shoot.md#function-setcooldown)**(float cooldown)<br>Sets the shoot cooldown.  |
| void | **[setActiveShootingType](Classes/classecs_1_1Shoot.md#function-setactiveshootingtype)**([ShootingType](Classes/classecs_1_1Shoot.md#enum-shootingtype) type) |
| float | **[getTimeSinceLastShot](Classes/classecs_1_1Shoot.md#function-gettimesincelastshot)**() const<br>Gets the last shot.  |
| float | **[getShootTimer](Classes/classecs_1_1Shoot.md#function-getshoottimer)**() const<br>Gets the shooter time.  |
| [Shoot::ShootingType](Classes/classecs_1_1Shoot.md#enum-shootingtype) | **[getRandomShootingType](Classes/classecs_1_1Shoot.md#function-getrandomshootingtype)**() |
| int | **[getDamage](Classes/classecs_1_1Shoot.md#function-getdamage)**() const<br>Gets the shoot damage.  |
| float | **[getCooldown](Classes/classecs_1_1Shoot.md#function-getcooldown)**() const<br>Gets the shoot cooldown.  |
| [ShootingType](Classes/classecs_1_1Shoot.md#enum-shootingtype) | **[getActiveShootingType](Classes/classecs_1_1Shoot.md#function-getactiveshootingtype)**() const |
| | **[Shoot](Classes/classecs_1_1Shoot.md#function-shoot)**(int damage, float cooldown, float shootTimer =0.0f) |

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

## Public Types Documentation

### enum ShootingType

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| Shotgun | |   |
| Normal | |   |
| Gatling | |   |




## Public Functions Documentation

### function ~Shoot

```cpp
~Shoot() override =default
```


### function updateShootingType

```cpp
void updateShootingType()
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


### function setShootTimer

```cpp
void setShootTimer(
    float cooldown
)
```

Sets the shooter. 

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


### function setActiveShootingType

```cpp
void setActiveShootingType(
    ShootingType type
)
```


### function getTimeSinceLastShot

```cpp
float getTimeSinceLastShot() const
```

Gets the last shot. 

**Return**: The last shot 

### function getShootTimer

```cpp
float getShootTimer() const
```

Gets the shooter time. 

**Return**: The shoot timer 

### function getRandomShootingType

```cpp
Shoot::ShootingType getRandomShootingType()
```


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

### function getActiveShootingType

```cpp
ShootingType getActiveShootingType() const
```


### function Shoot

```cpp
inline explicit Shoot(
    int damage,
    float cooldown,
    float shootTimer =0.0f
)
```


-------------------------------

Updated on 2026-01-18 at 21:54:06 +0000