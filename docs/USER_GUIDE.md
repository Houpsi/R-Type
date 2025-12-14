# R-Type: User Manual & Gameplay Guide

Welcome to **R-Type**! This document explains how to launch the game server, connect your client, and master the controls to defeat the Bydo Empire.

---

## 🚀 1. Launching the Game

R-Type is a networked game. You must launch the **Server** first, and then connect one or more **Clients**.

### Step 1: Start the Server
The server manages the game world. You need to provide a **Port** number for it to listen on.

**Command Syntax:**
```bash
./r-type_server <port>
# Example : ./r-type_server 4242
```
*Note: the port argument is **mandatory**, it should be between **1024** and **65535**.*

### Step 2: Start the Client

Once the **server** is running, launch the client to join the game.
You need to specify the **Server Port** first, followed by the **Server IP Address**.

**Command Syntax:**
```bash
./r-type_client <server_port> <server_ip>
# Example : ./r-type_client 4242 127.0.0.1
```
*Help: If you run the commands without arguments, the game will display a help message. 
**Error:** If the client cannot find the server, it will print "Failed to connect" and exit. Ensure the server is running first!*

---

## 🎮 2. Controls

The game supports both standard Arrow Keys and ZQSD layouts.

| Action        |   Option 1    | Option 2 |
|:--------------|:-------------:|---------:|
| Move UP       |  `Arrow up`   |      `Z` |
| Move DOWN     | `Arrow down`  |      `S` |
| Move LEFT     | `Arrow left`  |      `Q` |
| Move RIGHT    | `Arrow right` |      `D` |
| Shoot         |    `Space`    |  `Space` |
| Exit the game |   `Escape`    | `Escape` |

---

## 🕹️ 3. Gameplay Rules
### The Goal

Your objective is to fly through the levels, destroying waves of enemies and surviving until the end. This is a cooperative game—work with your teammates!

**Health & Death**
- **One-Hit Death**: Your ship is fragile. A single collision with an enemy or a projectile will destroy your ship.
- **Friendly Fire**: Be careful not to shoot your allies (if applicable) or crash into them.

**Multiplayer Mechanics**
- **Identification**: Each player ship has a distinct color so you can tell who is who.
- **Spectator Mode**:
  - If you die in a **Multiplayer** session, you are not kicked out! You will enter "Spectator Mode" and watch your teammates try to finish the level. You will respawn at the start of the next level (or if the team restarts).
  - If you die in **Solo** play, the level ends immediately.