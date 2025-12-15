---
title: server::Level

---

# server::Level






`#include <Level.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| uint8_t | **[getLevelId](Classes/classserver_1_1Level.md#function-getlevelid)**() const |
| bool | **[getIsBossPresent](Classes/classserver_1_1Level.md#function-getisbosspresent)**() const |
| uint8_t | **[getEnemySpawnRate](Classes/classserver_1_1Level.md#function-getenemyspawnrate)**() const |
| uint32_t | **[getBossApparitionTime](Classes/classserver_1_1Level.md#function-getbossapparitiontime)**() const |
| | **[Level](Classes/classserver_1_1Level.md#function-level)**(uint8_t levelId, uint8_t enemySpawnRate, bool isBossPresent, uint32_t bossApparitionTime) |

## Public Functions Documentation

### function getLevelId

```cpp
uint8_t getLevelId() const
```


### function getIsBossPresent

```cpp
bool getIsBossPresent() const
```


### function getEnemySpawnRate

```cpp
uint8_t getEnemySpawnRate() const
```


### function getBossApparitionTime

```cpp
uint32_t getBossApparitionTime() const
```


### function Level

```cpp
Level(
    uint8_t levelId,
    uint8_t enemySpawnRate,
    bool isBossPresent,
    uint32_t bossApparitionTime
)
```


-------------------------------

Updated on 2025-12-15 at 10:37:52 +0000