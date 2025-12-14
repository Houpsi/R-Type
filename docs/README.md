# R-Type

## 🚀 Description

This project is a networked implementation of the legendary horizontal shoot 'em up game **R-Type**. Developed in C++ as part of the Advanced C++ Knowledge Unit at Epitech, this game features a custom engine designed from scratch.

This version specifically focuses on **Advanced Gameplay** mechanics (Track #3), aiming to recreate the authentic feel of the 90s arcade classic while introducing modern multiplayer capabilities.

## ✨ Features (Track 3 Highlights)

### ⚙️ Core Engine
- **Custom ECS:** A robust Entity-Component-System allowing for high modularity and "composition over inheritance."
- **Decoupled Design:** Strict separation between the core Game Engine (systems, entities) and the Game Logic (R-Type rules).
- **Cross-Platform:** Runs on Linux and Windows.

### 🌐 Networking
- **Authoritative Server:** The server holds the truth. It handles all logic and replications to prevent cheating.
- **Binary Protocol:** Custom-designed binary protocol over UDP for low-latency gameplay updates.
- **Multithreading:** Fully multithreaded server architecture to handle multiple clients without blocking.
- **Scalability:** Support for up to 4 simultaneous players.

### 🎮 Gameplay & Graphics
- **Render Backend:** Powered by SFML.
- **Classic Feel:** Smooth horizontal scrolling with parallax starfields.
- **Audio System:** Integrated sound effects and music.
- **Enemies:** Implementation of the classic "Bydos" alien fleet.

## 🛠️ Installation

### Prerequisites
*   **C++ Compiler:** GCC, Clang, or MSVC supporting C++20.
*   **CMake:** Version 3.17 or higher.
*   **Package Manager:** Cmake cpm.
*   **Libraries:** SFML (Graphics/Audio/Network) - *Handled by the package manager.*

### Building the project

1.  Clone the repository:
    ```bash
    git clone https://github.com/EpitechPGE3-2025/G-CPP-500-LIL-5-2-rtype-10.git
    cd G-CPP-500-LIL-5-2-rtype-10
    ```

2.  Create a build directory and compile:
    ```bash
    # Linux / Mac
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build .

    # Windows
    mkdir build && cd build
    cmake ..
    cmake --build . --config Release
    ```

## 🎮 Usage

The project produces two binaries: `r-type_server` and `r-type_client`.

### Running the Server
Start the server first to accept incoming connections.
```bash
./r-type_server [port]
# Example: ./r-type_server 4242
```
### Running the Client
Launch the client to join the game
```bash
./r-type_client [port] [server_ip]
# Example: ./r-type_client 4242 localhost
```

## 🕹️ Controls
| Key   | Action              |
|-------|---------------------|
| Arrow | Move SpaceShip      |
| Space | Shoot / Charge Beam |
| Esc   | Menu / Quit         |


## 📚 Documentation
For more detailed information about the architecture and protocol, please refer to the documentation folder:
- [Gitbook](https://epitech-35.gitbook.io/r-type-save-gougougagaland/)

## 👥 Authors
- [Axel Desert](https://github.com/AxelDesert)
- [Helene Houplain](https://github.com/Houpsi)
- [Aleksandra Racine](https://github.com/Aleksrac)
- [Théo Garcia](https://github.com/theogarcia02)
- [Raphael Goncalves Dos Santos](https://github.com/raphaelGONCALVESDOSSANTOS)
