---
title: server::ServerSharedData

---

# server::ServerSharedData






`#include <ServerSharedData.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[setLobbyState](Classes/classserver_1_1ServerSharedData.md#function-setlobbystate)**(int lobbyId, cmn::LobbyState state) |
| void | **[removePlayerFromLobby](Classes/classserver_1_1ServerSharedData.md#function-removeplayerfromlobby)**(int playerId, int lobbyId) |
| size_t | **[getTcpPacketToSpecificPlayerQueueSize](Classes/classserver_1_1ServerSharedData.md#function-gettcppackettospecificplayerqueuesize)**() |
| std::optional< std::pair< int, cmn::packetData > > | **[getTcpPacketToSendToSpecificPlayer](Classes/classserver_1_1ServerSharedData.md#function-gettcppackettosendtospecificplayer)**() |
| std::optional< cmn::packetData > | **[getSystemPacket](Classes/classserver_1_1ServerSharedData.md#function-getsystempacket)**() |
| std::shared_ptr< sf::TcpSocket > | **[getPlayerSocket](Classes/classserver_1_1ServerSharedData.md#function-getplayersocket)**(int playerId) |
| int | **[getPlayerLobby](Classes/classserver_1_1ServerSharedData.md#function-getplayerlobby)**(int playerId) |
| size_t | **[getPlayerListSize](Classes/classserver_1_1ServerSharedData.md#function-getplayerlistsize)**() |
| std::optional< std::pair< int, sf::IpAddress > > | **[getPlayer](Classes/classserver_1_1ServerSharedData.md#function-getplayer)**(int playerId) |
| int | **[getNumberPlayerLobby](Classes/classserver_1_1ServerSharedData.md#function-getnumberplayerlobby)**(int lobbyId) |
| std::unordered_map< int, std::pair< int, sf::IpAddress > > | **[getMapPlayers](Classes/classserver_1_1ServerSharedData.md#function-getmapplayers)**() |
| std::optional< cmn::packetData > | **[getLobbyUdpReceivedPacket](Classes/classserver_1_1ServerSharedData.md#function-getlobbyudpreceivedpacket)**(int lobbyId) |
| size_t | **[getLobbyUdpQueueSize](Classes/classserver_1_1ServerSharedData.md#function-getlobbyudpqueuesize)**(int lobbyId) |
| std::optional< cmn::packetData > | **[getLobbyUdpPacketToSend](Classes/classserver_1_1ServerSharedData.md#function-getlobbyudppackettosend)**(int lobbyId) |
| std::optional< cmn::packetData > | **[getLobbyTcpReceivedPacket](Classes/classserver_1_1ServerSharedData.md#function-getlobbytcpreceivedpacket)**(int lobbyId) |
| size_t | **[getLobbyTcpQueueSize](Classes/classserver_1_1ServerSharedData.md#function-getlobbytcpqueuesize)**(int lobbyId) |
| std::optional< cmn::packetData > | **[getLobbyTcpPacketToSend](Classes/classserver_1_1ServerSharedData.md#function-getlobbytcppackettosend)**(int lobbyId) |
| std::optional< cmn::LobbyState > | **[getLobbyState](Classes/classserver_1_1ServerSharedData.md#function-getlobbystate)**(int lobbyId) |
| std::vector< int > | **[getLobbyPlayers](Classes/classserver_1_1ServerSharedData.md#function-getlobbyplayers)**(int lobbyId) |
| std::vector< int > | **[getAllPlayerIds](Classes/classserver_1_1ServerSharedData.md#function-getallplayerids)**() |
| std::vector< int > | **[getAllLobbyIds](Classes/classserver_1_1ServerSharedData.md#function-getalllobbyids)**() |
| void | **[deletePlayer](Classes/classserver_1_1ServerSharedData.md#function-deleteplayer)**(int playerId) |
| void | **[deleteLobby](Classes/classserver_1_1ServerSharedData.md#function-deletelobby)**(int lobbyId) |
| void | **[createLobby](Classes/classserver_1_1ServerSharedData.md#function-createlobby)**(int lobbyId) |
| void | **[addTcpPacketToSendToSpecificPlayer](Classes/classserver_1_1ServerSharedData.md#function-addtcppackettosendtospecificplayer)**(int playerId, const cmn::packetData & packet) |
| void | **[addSystemPacket](Classes/classserver_1_1ServerSharedData.md#function-addsystempacket)**(const cmn::packetData & packet) |
| void | **[addPlayerToLobby](Classes/classserver_1_1ServerSharedData.md#function-addplayertolobby)**(int playerId, int lobbyId) |
| void | **[addPlayer](Classes/classserver_1_1ServerSharedData.md#function-addplayer)**(int playerId, int port, const sf::IpAddress & ipAddress, std::shared_ptr< sf::TcpSocket > socket) |
| void | **[addLobbyUdpReceivedPacket](Classes/classserver_1_1ServerSharedData.md#function-addlobbyudpreceivedpacket)**(int lobbyId, const cmn::packetData & packet) |
| void | **[addLobbyUdpPacketToSend](Classes/classserver_1_1ServerSharedData.md#function-addlobbyudppackettosend)**(int lobbyId, const cmn::packetData & packet) |
| void | **[addLobbyTcpReceivedPacket](Classes/classserver_1_1ServerSharedData.md#function-addlobbytcpreceivedpacket)**(int lobbyId, const cmn::packetData & packet) |
| void | **[addLobbyTcpPacketToSend](Classes/classserver_1_1ServerSharedData.md#function-addlobbytcppackettosend)**(int lobbyId, const cmn::packetData & packet) |

## Public Functions Documentation

### function setLobbyState

```cpp
void setLobbyState(
    int lobbyId,
    cmn::LobbyState state
)
```


### function removePlayerFromLobby

```cpp
void removePlayerFromLobby(
    int playerId,
    int lobbyId
)
```


### function getTcpPacketToSpecificPlayerQueueSize

```cpp
size_t getTcpPacketToSpecificPlayerQueueSize()
```


### function getTcpPacketToSendToSpecificPlayer

```cpp
std::optional< std::pair< int, cmn::packetData > > getTcpPacketToSendToSpecificPlayer()
```


### function getSystemPacket

```cpp
std::optional< cmn::packetData > getSystemPacket()
```


### function getPlayerSocket

```cpp
std::shared_ptr< sf::TcpSocket > getPlayerSocket(
    int playerId
)
```


### function getPlayerLobby

```cpp
int getPlayerLobby(
    int playerId
)
```


### function getPlayerListSize

```cpp
size_t getPlayerListSize()
```


### function getPlayer

```cpp
std::optional< std::pair< int, sf::IpAddress > > getPlayer(
    int playerId
)
```


### function getNumberPlayerLobby

```cpp
int getNumberPlayerLobby(
    int lobbyId
)
```


### function getMapPlayers

```cpp
std::unordered_map< int, std::pair< int, sf::IpAddress > > getMapPlayers()
```


### function getLobbyUdpReceivedPacket

```cpp
std::optional< cmn::packetData > getLobbyUdpReceivedPacket(
    int lobbyId
)
```


### function getLobbyUdpQueueSize

```cpp
size_t getLobbyUdpQueueSize(
    int lobbyId
)
```


### function getLobbyUdpPacketToSend

```cpp
std::optional< cmn::packetData > getLobbyUdpPacketToSend(
    int lobbyId
)
```


### function getLobbyTcpReceivedPacket

```cpp
std::optional< cmn::packetData > getLobbyTcpReceivedPacket(
    int lobbyId
)
```


### function getLobbyTcpQueueSize

```cpp
size_t getLobbyTcpQueueSize(
    int lobbyId
)
```


### function getLobbyTcpPacketToSend

```cpp
std::optional< cmn::packetData > getLobbyTcpPacketToSend(
    int lobbyId
)
```


### function getLobbyState

```cpp
std::optional< cmn::LobbyState > getLobbyState(
    int lobbyId
)
```


### function getLobbyPlayers

```cpp
std::vector< int > getLobbyPlayers(
    int lobbyId
)
```


### function getAllPlayerIds

```cpp
std::vector< int > getAllPlayerIds()
```


### function getAllLobbyIds

```cpp
std::vector< int > getAllLobbyIds()
```


### function deletePlayer

```cpp
void deletePlayer(
    int playerId
)
```


### function deleteLobby

```cpp
void deleteLobby(
    int lobbyId
)
```


### function createLobby

```cpp
void createLobby(
    int lobbyId
)
```


### function addTcpPacketToSendToSpecificPlayer

```cpp
void addTcpPacketToSendToSpecificPlayer(
    int playerId,
    const cmn::packetData & packet
)
```


### function addSystemPacket

```cpp
void addSystemPacket(
    const cmn::packetData & packet
)
```


### function addPlayerToLobby

```cpp
void addPlayerToLobby(
    int playerId,
    int lobbyId
)
```


### function addPlayer

```cpp
void addPlayer(
    int playerId,
    int port,
    const sf::IpAddress & ipAddress,
    std::shared_ptr< sf::TcpSocket > socket
)
```


### function addLobbyUdpReceivedPacket

```cpp
void addLobbyUdpReceivedPacket(
    int lobbyId,
    const cmn::packetData & packet
)
```


### function addLobbyUdpPacketToSend

```cpp
void addLobbyUdpPacketToSend(
    int lobbyId,
    const cmn::packetData & packet
)
```


### function addLobbyTcpReceivedPacket

```cpp
void addLobbyTcpReceivedPacket(
    int lobbyId,
    const cmn::packetData & packet
)
```


### function addLobbyTcpPacketToSend

```cpp
void addLobbyTcpPacketToSend(
    int lobbyId,
    const cmn::packetData & packet
)
```


-------------------------------

Updated on 2026-01-18 at 21:54:06 +0000