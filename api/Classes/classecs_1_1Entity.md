---
title: ecs::Entity

---

# ecs::Entity






`#include <Entity.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[~Entity](Classes/classecs_1_1Entity.md#function-~entity)**() =default |
| template <typename T \> <br>void | **[removeComponent](Classes/classecs_1_1Entity.md#function-removecomponent)**() |
| uint32_t | **[getId](Classes/classecs_1_1Entity.md#function-getid)**() const |
| template <typename T \> <br>std::shared_ptr< T > | **[getComponent](Classes/classecs_1_1Entity.md#function-getcomponent)**() |
| template <typename T ,typename... Args\> <br>std::shared_ptr< T > | **[addComponent](Classes/classecs_1_1Entity.md#function-addcomponent)**(Args &&... args) |
| template <typename T \> <br>std::shared_ptr< T > | **[addComponent](Classes/classecs_1_1Entity.md#function-addcomponent)**() |
| | **[Entity](Classes/classecs_1_1Entity.md#function-entity)**(uint32_t id) |

## Public Functions Documentation

### function ~Entity

```cpp
~Entity() =default
```


### function removeComponent

```cpp
template <typename T >
inline void removeComponent()
```


### function getId

```cpp
uint32_t getId() const
```


### function getComponent

```cpp
template <typename T >
inline std::shared_ptr< T > getComponent()
```


### function addComponent

```cpp
template <typename T ,
typename... Args>
inline std::shared_ptr< T > addComponent(
    Args &&... args
)
```


### function addComponent

```cpp
template <typename T >
inline std::shared_ptr< T > addComponent()
```


### function Entity

```cpp
inline explicit Entity(
    uint32_t id
)
```


-------------------------------

Updated on 2026-01-18 at 21:46:45 +0000