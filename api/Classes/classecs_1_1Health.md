---
title: ecs::Health

---

# ecs::Health






`#include <Health.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Health](Classes/classecs_1_1Health.md#function-~health)**() override =default |
| void | **[setHealth](Classes/classecs_1_1Health.md#function-sethealth)**(int const health)<br>Sets the health.  |
| int | **[getHealth](Classes/classecs_1_1Health.md#function-gethealth)**() const |
| | **[Health](Classes/classecs_1_1Health.md#function-health)**(int const health) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~Health

```cpp
~Health() override =default
```


### function setHealth

```cpp
void setHealth(
    int const health
)
```

Sets the health. 

**Parameters**: 

  * **health** New health of the component 


### function getHealth

```cpp
int getHealth() const
```


**Return**: the health of the component 

@breif Gets the health 


### function Health

```cpp
explicit Health(
    int const health
)
```


-------------------------------

Updated on 2026-01-18 at 21:46:45 +0000