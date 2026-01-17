---
title: ecs::Sound

---

# ecs::Sound






`#include <Sound.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Sound](Classes/classecs_1_1Sound.md#function-~sound)**() override =default |
| void | **[setIsPlayed](Classes/classecs_1_1Sound.md#function-setisplayed)**(bool played) |
| void | **[setIsLoopping](Classes/classecs_1_1Sound.md#function-setisloopping)**(bool loop) |
| bool | **[getIsPlayed](Classes/classecs_1_1Sound.md#function-getisplayed)**() const |
| int | **[getIsLoopping](Classes/classecs_1_1Sound.md#function-getisloopping)**() |
| int | **[getIdMusic](Classes/classecs_1_1Sound.md#function-getidmusic)**() const |
| | **[Sound](Classes/classecs_1_1Sound.md#function-sound)**(int id, bool loop) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function ~Sound

```cpp
~Sound() override =default
```


### function setIsPlayed

```cpp
void setIsPlayed(
    bool played
)
```


### function setIsLoopping

```cpp
void setIsLoopping(
    bool loop
)
```


### function getIsPlayed

```cpp
bool getIsPlayed() const
```


### function getIsLoopping

```cpp
int getIsLoopping()
```


### function getIdMusic

```cpp
int getIdMusic() const
```


### function Sound

```cpp
inline explicit Sound(
    int id,
    bool loop
)
```


-------------------------------

Updated on 2026-01-17 at 13:41:27 +0000