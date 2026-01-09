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
| void | **[play](Classes/classecs_1_1Sound.md#function-play)**()<br>PLay the sound of the component.  |
| const sf::Sound & | **[getSound](Classes/classecs_1_1Sound.md#function-getsound)**() const<br>Gets [Sound](Classes/classecs_1_1Sound.md) of the component.  |
| | **[Sound](Classes/classecs_1_1Sound.md#function-sound)**(const std::string & filepath) |

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


### function play

```cpp
void play()
```

PLay the sound of the component. 

### function getSound

```cpp
const sf::Sound & getSound() const
```

Gets [Sound](Classes/classecs_1_1Sound.md) of the component. 

**Return**: the sound of the component 

### function Sound

```cpp
Sound(
    const std::string & filepath
)
```


**Parameters**: 

  * **filepath** The path to the sound file 


@bried Load the sound from a file 


-------------------------------

Updated on 2026-01-09 at 13:36:43 +0000