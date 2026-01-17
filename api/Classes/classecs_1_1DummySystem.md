---
title: ecs::DummySystem

---

# ecs::DummySystem





Inherits from [ecs::System](Classes/classecs_1_1System.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](Classes/classecs_1_1DummySystem.md#function-update)**([EcsManager](Classes/classecs_1_1EcsManager.md) & manager) override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| bool | **[updated](Classes/classecs_1_1DummySystem.md#variable-updated)**  |

## Additional inherited members

**Public Functions inherited from [ecs::System](Classes/classecs_1_1System.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~System](Classes/classecs_1_1System.md#function-~system)**() =default |
| | **[System](Classes/classecs_1_1System.md#function-system)**() =default |


## Public Functions Documentation

### function update

```cpp
inline virtual void update(
    EcsManager & manager
) override
```


**Reimplements**: [ecs::System::update](Classes/classecs_1_1System.md#function-update)


## Public Attributes Documentation

### variable updated

```cpp
bool updated = false;
```


-------------------------------

Updated on 2026-01-17 at 16:36:40 +0000