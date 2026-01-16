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
| uint64_t | **[getId](Classes/classecs_1_1Entity.md#function-getid)**() const |
| template <typename T \> <br>std::shared_ptr< T > | **[getComponent](Classes/classecs_1_1Entity.md#function-getcomponent)**() |
| template <typename T ,typename... Args\> <br>std::shared_ptr< T > | **[addComponent](Classes/classecs_1_1Entity.md#function-addcomponent)**(Args &&... args) |
| template <typename T \> <br>std::shared_ptr< T > | **[addComponent](Classes/classecs_1_1Entity.md#function-addcomponent)**() |
| | **[Entity](Classes/classecs_1_1Entity.md#function-entity)**(uint64_t id) |

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
uint64_t getId() const
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
    uint64_t id
)
```


-------------------------------

Updated on 2026-01-16 at 09:38:10 +0000