# R-Type

![R-Type Banner](https://lien-image-jeu)
<!-- mettre image jeu -->

[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows-blue)]()

## 🚀 Description

This project is a networked implementation of the legendary horizontal shoot 'em up game **R-Type**. Developed in C++ as part of the Advanced C++ Knowledge Unit at Epitech, this game features a custom engine designed from scratch.

This version specifically focuses on **Advanced Gameplay** mechanics (Track #3), aiming to recreate the authentic feel of the 90s arcade classic while introducing modern multiplayer capabilities.

## ✨ Features (Track 3 Highlights)

### Core Engine
- **Multi-threaded Server:** Authoritative server handling game logic and state.
- **UDP Networking:** Fast binary protocol for real-time entity updates.
- **Cross-Platform:** Runs on Linux and Windows.

### Gameplay & Content
- **feature:** description

## 🛠️ Installation

### Prerequisites
*   **C++ Compiler:** GCC, Clang, or MSVC supporting C++20.
*   **CMake:** Version 3.17 or higher.
*   **Package Manager:** Cmake cpm.
*   **Libraries:** SFML (Graphics/Audio/Network) - *Handled by the package manager.*

### Building the project

1.  Clone the repository:
    ```bash
    git clone https://github.com/username/r-type.git
    cd r-type
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
### Running the client
Launch the client to join the game
```bash
./r-type_client [port]
# Example: ./r-type_server 4242
```

## 🕹️ Controls
| Key   | Action              |
|-------|---------------------|
| Arrow | Move SpaceShip      |
| Space | Shoot / Charge Beam |
| Esc   | Menu / Quit         |


## 📚 Documentation
For more detailed information about the architecture and protocol, please refer to the documentation folder:
- [Developer Documentation](http://inserer-un-lien)
- [Network Protocol](http://inserer-un-lien)
- [Technical & Comparative Study](http://inserer-un-lien)

## 👥 Authors
- [Axel Desert](https://github.com/AxelDesert)
- [Helene Houplain](https://github.com/Houpsi)
- [Aleksandra Racine](https://github.com/Aleksrac)
- [Théo Garcia](https://github.com/theogarcia02)
- [Raphael Goncalves Dos Santos](https://github.com/raphaelGONCALVESDOSSANTOS)
