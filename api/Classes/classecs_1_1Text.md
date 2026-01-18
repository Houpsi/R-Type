---
title: ecs::Text

---

# ecs::Text






`#include <Text.hpp>`

Inherits from [ecs::Component](Classes/classecs_1_1Component.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[setString](Classes/classecs_1_1Text.md#function-setstring)**(const std::string & str) |
| sf::Text & | **[getText](Classes/classecs_1_1Text.md#function-gettext)**() |
| const sf::Text & | **[getText](Classes/classecs_1_1Text.md#function-gettext)**() const |
| | **[Text](Classes/classecs_1_1Text.md#function-text)**(const sf::Font & font, unsigned int size =24, sf::Color color =sf::Color::White) |

## Additional inherited members

**Public Functions inherited from [ecs::Component](Classes/classecs_1_1Component.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Component](Classes/classecs_1_1Component.md#function-~component)**() =default |
| | **[Component](Classes/classecs_1_1Component.md#function-component)**() =default |


## Public Functions Documentation

### function setString

```cpp
void setString(
    const std::string & str
)
```


### function getText

```cpp
sf::Text & getText()
```


### function getText

```cpp
const sf::Text & getText() const
```


### function Text

```cpp
Text(
    const sf::Font & font,
    unsigned int size =24,
    sf::Color color =sf::Color::White
)
```


-------------------------------

Updated on 2026-01-18 at 10:07:04 +0000