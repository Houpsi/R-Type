# Technical and Comparative Study

As part of the development of our multiplayer R-Type game engine, we conducted a thorough comparative study to select the technologies and architectures best suited to real-time constraints and performance requirements.

## 1. Software Architecture: ECS vs. Object-Oriented Programming (OOP)

Choosing the right architecture is critical for a video game managing multiple entities (spaceships, missiles, enemies, scenery). We compared the classical inheritance-based approach against the data composition approach.

### A. The Classical Approach: Inheritance (OOP)
The traditional approach consists of creating a class hierarchy (e.g., `Entity` -> `Movable` -> `Ship` -> `Player`).
* **Identified Limitations:**
    * **The Diamond Problem:** Difficulty in having an object inherit multiple behaviors without complicating the inheritance tree.
    * **Rigidity:** Modifying an enemy's behavior at "runtime" is complex.
    * **Performance (Cache Misses):** In OOP, objects are scattered throughout memory. The processor wastes time fetching data, causing frequent *cache misses*.

### B. Our Choice: Entity Component System (ECS)

We opted for an **ECS** architecture, which favors "Composition over Inheritance."
* **Entity:** A simple ID (unique integer).
* **Component:** A container for pure data, e.g., `Position`, `Velocity`, `Sprite`.
* **System:** The logic that iterates over entities possessing the required components.

### Justification of Choice
1.  **Project Bootstrap Foundation:** This architecture was introduced to us during the project bootstrap. Utilizing this foundation allowed us to build upon a verified base structure rather than starting from scratch.
2.  **Memory Optimization (Data Locality):** ECS allows components of the same type to be stored contiguously in memory. This enables the CPU to prefetch data into the cache (L1/L2), offering significant performance gains when processing hundreds of missiles or enemies.

---

## 2. Graphics Library Selection: SFML vs. SDL2 vs. Raylib

For 2D rendering and input management, we evaluated three major C++ compatible solutions.

| Criteria | SDL2 | Raylib | SFML (Chosen) |
| :--- | :--- | :--- | :--- |
| **Paradigm** | C (Functional/Procedural) | C (Modern) | C++ (Object Oriented) |
| **Architecture** | Low-level, requires wrappers | Simple, very high-level | Native Object Oriented |
| **Module Management** | Graphics, Audio, Input | All-in-one | Modular (System, Window, Graphics, Network) |

### Justification for Choosing SFML
Although SDL2 is an industry standard due to its portability, we selected **SFML** for the following reasons:
* **Language Consistency:** SFML is written in modern C++. Its Object-Oriented API integrates naturally with our codebase and classes, avoiding the need to write "wrappers" as would have been necessary with SDL2 (which is written in C).
* **Integrated Modules:** SFML natively provides utility classes for time management (`sf::Clock`, `sf::Time`) and threads, which are essential for synchronizing the *Game Loop* with the network without relying on heavy third-party libraries like Boost.

---

## 3. Network Protocols: TCP vs. UDP

The core of the R-Type project lies in its ability to synchronize game state between multiple clients and a server in real-time. The choice of transport protocol is decisive for the user experience.

### A. TCP (Transmission Control Protocol)
TCP guarantees that packets arrive in order and without errors.
* **The Real-Time Problem:** If a packet is lost, TCP blocks the reading of subsequent packets until the lost packet is retransmitted (Head-of-line blocking). This creates latency spikes that are unacceptable for a fast-paced shooter.

### B. UDP (User Datagram Protocol)
UDP sends packets without guaranteeing their delivery or order of arrival.
* **Advantage:** It is the fastest protocol. If a position packet is lost, it is not critical, as the packet for the next frame (arriving 16ms later) will contain more up-to-date position data.

### Justification of Implementation
For our R-Type, we justified the use of a differentiated (hybrid) network architecture:

1.  **Gameplay (UDP):** Entity positions, shots, and health statuses are sent via UDP. Fluidity takes precedence over the absolute accuracy of every single packet. We implement a client-side **interpolation** system to smooth out movements between two received UDP packets.
2.  **Critical Commands (TCP):** For actions that must absolutely not be lost (Lobby connection, Game start), we use TCP.

**Conclusion:** Relying exclusively on TCP would have rendered the game unplayable in the event of network micro-stutters. Using UDP for the main game loop is the only technically viable solution to ensure the necessary responsiveness.