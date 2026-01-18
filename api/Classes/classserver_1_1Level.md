---
title: server::Level

---

# server::Level






`#include <Level.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[setRepeatWaves](Classes/classserver_1_1Level.md#function-setrepeatwaves)**(uint8_t numberWaves) |
| void | **[setPlayerSpeed](Classes/classserver_1_1Level.md#function-setplayerspeed)**(uint16_t playerSpeed) |
| void | **[setNameLevel](Classes/classserver_1_1Level.md#function-setnamelevel)**(const std::string & _nameLevel) |
| void | **[setLevelId](Classes/classserver_1_1Level.md#function-setlevelid)**(uint8_t levelId) |
| void | **[setIsBossPresent](Classes/classserver_1_1Level.md#function-setisbosspresent)**(bool isPresent) |
| void | **[setCurrentWave](Classes/classserver_1_1Level.md#function-setcurrentwave)**(int id) |
| void | **[setBossSpawned](Classes/classserver_1_1Level.md#function-setbossspawned)**(bool spawned) |
| void | **[setBoss](Classes/classserver_1_1Level.md#function-setboss)**(std::string boss, uint32_t healthBoss) |
| void | **[setBonusSpawnRate](Classes/classserver_1_1Level.md#function-setbonusspawnrate)**(float spawnRate) |
| void | **[nextWave](Classes/classserver_1_1Level.md#function-nextwave)**() |
| bool | **[isFinished](Classes/classserver_1_1Level.md#function-isfinished)**() const |
| bool | **[hasBossSpawned](Classes/classserver_1_1Level.md#function-hasbossspawned)**() const |
| const std::vector< std::pair< uint16_t, std::list< [tmpEnemy](Classes/structtmpEnemy.md) > > > & | **[getWaves](Classes/classserver_1_1Level.md#function-getwaves)**() const |
| std::vector< std::pair< uint16_t, std::list< [tmpEnemy](Classes/structtmpEnemy.md) > > > & | **[getWaves](Classes/classserver_1_1Level.md#function-getwaves)**() |
| uint8_t | **[getRepeatWaves](Classes/classserver_1_1Level.md#function-getrepeatwaves)**() const |
| uint16_t | **[getPlayerSpeed](Classes/classserver_1_1Level.md#function-getplayerspeed)**() const |
| std::string | **[getNameLevel](Classes/classserver_1_1Level.md#function-getnamelevel)**() const |
| uint8_t | **[getLevelId](Classes/classserver_1_1Level.md#function-getlevelid)**() const |
| bool | **[getIsBossPresent](Classes/classserver_1_1Level.md#function-getisbosspresent)**() const |
| uint8_t | **[getEnemySpawnRate](Classes/classserver_1_1Level.md#function-getenemyspawnrate)**() const |
| int | **[getCurrentWaveId](Classes/classserver_1_1Level.md#function-getcurrentwaveid)**() const |
| std::pair< std::string, uint32_t > | **[getBoss](Classes/classserver_1_1Level.md#function-getboss)**() const |
| float | **[getBonusSpawnRate](Classes/classserver_1_1Level.md#function-getbonusspawnrate)**() const |
| void | **[calculateNumberTotalWave](Classes/classserver_1_1Level.md#function-calculatenumbertotalwave)**() |
| void | **[addWave](Classes/classserver_1_1Level.md#function-addwave)**(uint16_t time, std::list< [tmpEnemy](Classes/structtmpEnemy.md) > enemies) |
| | **[Level](Classes/classserver_1_1Level.md#function-level)**() =default |

## Public Functions Documentation

### function setRepeatWaves

```cpp
void setRepeatWaves(
    uint8_t numberWaves
)
```


### function setPlayerSpeed

```cpp
void setPlayerSpeed(
    uint16_t playerSpeed
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


### function setCurrentWave

```cpp
void setCurrentWave(
    int id
)
```


### function setBossSpawned

```cpp
void setBossSpawned(
    bool spawned
)
```


### function setBoss

```cpp
void setBoss(
    std::string boss,
    uint32_t healthBoss
)
```


### function setBonusSpawnRate

```cpp
void setBonusSpawnRate(
    float spawnRate
)
```


### function nextWave

```cpp
void nextWave()
```


### function isFinished

```cpp
bool isFinished() const
```


### function hasBossSpawned

```cpp
bool hasBossSpawned() const
```


### function getWaves

```cpp
const std::vector< std::pair< uint16_t, std::list< tmpEnemy > > > & getWaves() const
```


### function getWaves

```cpp
std::vector< std::pair< uint16_t, std::list< tmpEnemy > > > & getWaves()
```


### function getRepeatWaves

```cpp
uint8_t getRepeatWaves() const
```


### function getPlayerSpeed

```cpp
uint16_t getPlayerSpeed() const
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


### function getCurrentWaveId

```cpp
int getCurrentWaveId() const
```


### function getBoss

```cpp
std::pair< std::string, uint32_t > getBoss() const
```


### function getBonusSpawnRate

```cpp
float getBonusSpawnRate() const
```


### function calculateNumberTotalWave

```cpp
void calculateNumberTotalWave()
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

Updated on 2026-01-18 at 21:46:45 +0000