---
title: server::Server

---

# server::Server






`#include <Server.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| int | **[sendUdp](Classes/classserver_1_1Server.md#function-sendudp)**(cmn::CustomPacket packet, const sf::IpAddress & clientIp, uint16_t port) |
| void | **[sendTcpToPlayer](Classes/classserver_1_1Server.md#function-sendtcptoplayer)**(int playerId, const cmn::CustomPacket & packet) |
| int | **[sendTcp](Classes/classserver_1_1Server.md#function-sendtcp)**(cmn::CustomPacket packet, sf::TcpSocket & clientSocket) |
| void | **[run](Classes/classserver_1_1Server.md#function-run)**() |
| void | **[close](Classes/classserver_1_1Server.md#function-close)**() |
| void | **[broadcastUdpToLobby](Classes/classserver_1_1Server.md#function-broadcastudptolobby)**(int lobbyId, const cmn::CustomPacket & packet) |
| void | **[broadcastUdp](Classes/classserver_1_1Server.md#function-broadcastudp)**(const cmn::CustomPacket & packet) |
| void | **[broadcastTcpToLobby](Classes/classserver_1_1Server.md#function-broadcasttcptolobby)**(int lobbyId, const cmn::CustomPacket & packet) |
| void | **[broadcastTcp](Classes/classserver_1_1Server.md#function-broadcasttcp)**(const cmn::CustomPacket & packet) const |
| int | **[bindPorts](Classes/classserver_1_1Server.md#function-bindports)**(uint16_t port) |
| | **[Server](Classes/classserver_1_1Server.md#function-server)**(const std::shared_ptr< [ServerSharedData](Classes/classserver_1_1ServerSharedData.md) > & data) |

## Public Functions Documentation

### function sendUdp

```cpp
int sendUdp(
    cmn::CustomPacket packet,
    const sf::IpAddress & clientIp,
    uint16_t port
)
```


### function sendTcpToPlayer

```cpp
void sendTcpToPlayer(
    int playerId,
    const cmn::CustomPacket & packet
)
```


### function sendTcp

```cpp
static int sendTcp(
    cmn::CustomPacket packet,
    sf::TcpSocket & clientSocket
)
```


### function run

```cpp
void run()
```


### function close

```cpp
void close()
```


### function broadcastUdpToLobby

```cpp
void broadcastUdpToLobby(
    int lobbyId,
    const cmn::CustomPacket & packet
)
```


### function broadcastUdp

```cpp
void broadcastUdp(
    const cmn::CustomPacket & packet
)
```


### function broadcastTcpToLobby

```cpp
void broadcastTcpToLobby(
    int lobbyId,
    const cmn::CustomPacket & packet
)
```


### function broadcastTcp

```cpp
void broadcastTcp(
    const cmn::CustomPacket & packet
) const
```


### function bindPorts

```cpp
int bindPorts(
    uint16_t port
)
```


### function Server

```cpp
explicit Server(
    const std::shared_ptr< ServerSharedData > & data
)
```


-------------------------------

Updated on 2026-01-18 at 11:25:11 +0000