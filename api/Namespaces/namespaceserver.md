---
title: server

---

# server



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[server::ServerSharedData](Classes/classserver_1_1ServerSharedData.md)**  |
| class | **[server::Server](Classes/classserver_1_1Server.md)**  |
| class | **[server::Parser](Classes/classserver_1_1Parser.md)**  |
| class | **[server::LobbyManager](Classes/classserver_1_1LobbyManager.md)**  |
| class | **[server::LevelParser](Classes/classserver_1_1LevelParser.md)**  |
| class | **[server::LevelManager](Classes/classserver_1_1LevelManager.md)**  |
| class | **[server::Level](Classes/classserver_1_1Level.md)**  |
| class | **[server::Game](Classes/classserver_1_1Game.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| using [Lobby](Namespaces/namespaceserver.md#using-lobby) { int id | **[Lobby](Namespaces/namespaceserver.md#using-lobby)**  |

## Attributes

|                | Name           |
| -------------- | -------------- |
| cmn::LobbyType | **[type](Namespaces/namespaceserver.md#variable-type)**  |
| cmn::LobbyState | **[state](Namespaces/namespaceserver.md#variable-state)**  |
| std::chrono::steady_clock::time_point | **[createdAt](Namespaces/namespaceserver.md#variable-createdat)**  |
| int | **[code](Namespaces/namespaceserver.md#variable-code)**  |

## Types Documentation

### using Lobby

```cpp
using server::Lobby = typedef Lobby { int id;
```




## Attributes Documentation

### variable type

```cpp
cmn::LobbyType type;
```


### variable state

```cpp
cmn::LobbyState state;
```


### variable createdAt

```cpp
std::chrono::steady_clock::time_point createdAt;
```


### variable code

```cpp
int code;
```





-------------------------------

Updated on 2026-01-18 at 11:25:11 +0000