---
title: server::Server

---

# server::Server






`#include <Server.hpp>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| int | **[sendUdp](Classes/classserver_1_1Server.md#function-sendudp)**(cmn::CustomPacket packet, const sf::IpAddress & clientIp, uint16_t port) |
| int | **[sendTcp](Classes/classserver_1_1Server.md#function-sendtcp)**(cmn::CustomPacket packet, sf::TcpSocket & clientSocket) |
| void | **[run](Classes/classserver_1_1Server.md#function-run)**() |
| void | **[close](Classes/classserver_1_1Server.md#function-close)**() |
| void | **[broadcastUdp](Classes/classserver_1_1Server.md#function-broadcastudp)**(const cmn::CustomPacket & packet) |
| void | **[broadcastTcp](Classes/classserver_1_1Server.md#function-broadcasttcp)**(const cmn::CustomPacket & packet) const |
| int | **[bindPorts](Classes/classserver_1_1Server.md#function-bindports)**(uint16_t port) |
| | **[Server](Classes/classserver_1_1Server.md#function-server)**(std::shared_ptr< cmn::SharedData > & data) |

## Public Functions Documentation

### function sendUdp

```cpp
int sendUdp(
    cmn::CustomPacket packet,
    const sf::IpAddress & clientIp,
    uint16_t port
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


### function broadcastUdp

```cpp
void broadcastUdp(
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
    std::shared_ptr< cmn::SharedData > & data
)
```


-------------------------------

Updated on 2026-01-16 at 09:38:10 +0000