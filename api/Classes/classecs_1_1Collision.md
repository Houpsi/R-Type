---
title: ecs::Collision

---

# ecs::Collision






`#include <Collision.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Collision](Classes/classecs_1_1Collision.md#function-~collision)**() =default |
| void | **[setWidth](Classes/classecs_1_1Collision.md#function-setwidth)**(float width) |
| void | **[setTypeCollision](Classes/classecs_1_1Collision.md#function-settypecollision)**([TypeCollision](Namespaces/namespaceecs.md#enum-typecollision) typeCollision)<br>Sets the collision type.  |
| void | **[setIsTrigger](Classes/classecs_1_1Collision.md#function-setistrigger)**(bool isTrigger)<br>Defines whether this collider is a trigger.  |
| void | **[setHeight](Classes/classecs_1_1Collision.md#function-setheight)**(float height)<br>Sets the collider height.  |
| float | **[getWidth](Classes/classecs_1_1Collision.md#function-getwidth)**() const<br>Gets the collider width.  |
| [TypeCollision](Namespaces/namespaceecs.md#enum-typecollision) | **[getTypeCollision](Classes/classecs_1_1Collision.md#function-gettypecollision)**() const<br>Returns the collision type.  |
| bool | **[getIsTrigger](Classes/classecs_1_1Collision.md#function-getistrigger)**() const<br>Checks whether this collider is a trigger A trigger detects collisions without producing physical blocking.  |
| float | **[getHeight](Classes/classecs_1_1Collision.md#function-getheight)**() const<br>Gets the collider height.  |
| | **[Collision](Classes/classecs_1_1Collision.md#function-collision)**([TypeCollision](Namespaces/namespaceecs.md#enum-typecollision) typeColision, float height, float width) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~Collision

```cpp
~Collision() =default
```


### function setWidth

```cpp
void setWidth(
    float width
)
```


**Parameters**: 

  * **width** New width of the collider 


@bried Sets the collider width 


### function setTypeCollision

```cpp
void setTypeCollision(
    TypeCollision typeCollision
)
```

Sets the collision type. 

**Parameters**: 

  * **typeCollision** The new collision type 


### function setIsTrigger

```cpp
void setIsTrigger(
    bool isTrigger
)
```

Defines whether this collider is a trigger. 

**Parameters**: 

  * **isTrigger** True to make this collider a trigger 


### function setHeight

```cpp
void setHeight(
    float height
)
```

Sets the collider height. 

**Parameters**: 

  * **height** New height of the collider 


### function getWidth

```cpp
float getWidth() const
```

Gets the collider width. 

**Return**: The width of the collider 

### function getTypeCollision

```cpp
TypeCollision getTypeCollision() const
```

Returns the collision type. 

**Return**: The TypeCollision value representing the kind of collision 

### function getIsTrigger

```cpp
bool getIsTrigger() const
```

Checks whether this collider is a trigger A trigger detects collisions without producing physical blocking. 

**Return**: True if the collider is a trigger, false otherwise 

### function getHeight

```cpp
float getHeight() const
```

Gets the collider height. 

**Return**: The height of the collider 

### function Collision

```cpp
inline explicit Collision(
    TypeCollision typeColision,
    float height,
    float width
)
```


-------------------------------

Updated on 2025-12-15 at 09:18:33 +0000