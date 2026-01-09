---
title: server::Level

---

# server::Level






`#include <Level.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[setPlayerSpeed](Classes/classserver_1_1Level.md#function-setplayerspeed)**(uint16_t playerSpeed) |
| void | **[setNumberWaves](Classes/classserver_1_1Level.md#function-setnumberwaves)**(uint8_t numberWaves) |
| void | **[setNameLevel](Classes/classserver_1_1Level.md#function-setnamelevel)**(const std::string & _nameLevel) |
| void | **[setLevelId](Classes/classserver_1_1Level.md#function-setlevelid)**(uint8_t levelId) |
| void | **[setIsBossPresent](Classes/classserver_1_1Level.md#function-setisbosspresent)**(bool isPresent) |
| void | **[setBoss](Classes/classserver_1_1Level.md#function-setboss)**(std::string boss, uint32_t healthBoss) |
| std::list< std::pair< uint16_t, std::list< [tmpEnemy](Classes/structtmpEnemy.md) > > > | **[getWaves](Classes/classserver_1_1Level.md#function-getwaves)**() const |
| uint16_t | **[getPlayerSpeed](Classes/classserver_1_1Level.md#function-getplayerspeed)**() const |
| uint8_t | **[getNumberWaves](Classes/classserver_1_1Level.md#function-getnumberwaves)**() const |
| std::string | **[getNameLevel](Classes/classserver_1_1Level.md#function-getnamelevel)**() const |
| uint8_t | **[getLevelId](Classes/classserver_1_1Level.md#function-getlevelid)**() const |
| bool | **[getIsBossPresent](Classes/classserver_1_1Level.md#function-getisbosspresent)**() const |
| uint8_t | **[getEnemySpawnRate](Classes/classserver_1_1Level.md#function-getenemyspawnrate)**() const |
| std::pair< std::string, uint32_t > | **[getBoss](Classes/classserver_1_1Level.md#function-getboss)**() const |
| void | **[addWave](Classes/classserver_1_1Level.md#function-addwave)**(uint16_t time, std::list< [tmpEnemy](Classes/structtmpEnemy.md) > enemies) |
| | **[Level](Classes/classserver_1_1Level.md#function-level)**() =default |

## Public Functions Documentation

### function setPlayerSpeed

```cpp
void setPlayerSpeed(
    uint16_t playerSpeed
)
```


### function setNumberWaves

```cpp
void setNumberWaves(
    uint8_t numberWaves
)
```


### function setNameLevel

```cpp
void setNameLevel(
    const std::string & _nameLevel
)
```


### function setLevelId

```cpp
void setLevelId(
    uint8_t levelId
)
```


### function setIsBossPresent

```cpp
void setIsBossPresent(
    bool isPresent
)
```


### function setBoss

```cpp
void setBoss(
    std::string boss,
    uint32_t healthBoss
)
```


### function getWaves

```cpp
std::list< std::pair< uint16_t, std::list< tmpEnemy > > > getWaves() const
```


### function getPlayerSpeed

```cpp
uint16_t getPlayerSpeed() const
```


### function getNumberWaves

```cpp
uint8_t getNumberWaves() const
```


### function getNameLevel

```cpp
std::string getNameLevel() const
```


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


### function getBoss

```cpp
std::pair< std::string, uint32_t > getBoss() const
```


### function addWave

```cpp
void addWave(
    uint16_t time,
    std::list< tmpEnemy > enemies
)
```


### function Level

```cpp
Level() =default
```


-------------------------------

Updated on 2026-01-09 at 13:36:43 +0000