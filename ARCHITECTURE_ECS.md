# Software Architecture & Internals

This document details the internal design of the **R-Type Game Engine**.
The engine is built upon a custom **Object-Oriented Entity-Component-System (ECS)** architecture, designed for modularity and network replication.

---

## 📊 Class Diagram

Click the link below to visualize the relationship between the `EcsManager`, `Entity`, `Components`, and `Systems`.

[**> View Full Architecture Diagram (Lucidchart)**](https://lucid.app/lucidchart/d7494efd-aa0c-409f-a5d8-0528223e1618/edit?viewport_loc=-3379%2C-1360%2C4371%2C2029%2CHWEp-vi-RSFO&invitationId=inv_aaf5b920-9bbc-4d28-83a8-133ea61f1f62)

---

## 1. The ECS Pattern

Unlike strict Data-Oriented ECS (which uses contiguous memory arrays), our engine uses an **Object-Oriented approach**. This favors ease of use, safety (`std::shared_ptr`), and flexibility over raw cache-locality performance.

### 🧠 The Core: EcsManager
The `EcsManager` acts as the "World" or "Context".
* It owns all **Entities** (`std::vector<std::shared_ptr<Entity>>`).
* It owns all **Systems**.
* It manages the **Game Loop** via `updateSystems()`.
* It holds global resources (DeltaTime, ResourceManager).

### 📦 Entities
An `Entity` is not just an ID; it is a **Container Object**.
* **Structure:** It holds a list of its own components: `std::vector<std::shared_ptr<Component>>`.
* **Identification:** Each entity has a unique `uint64_t` ID.
* **Lifecycle:** Entities are dynamically allocated on the Heap.

### 🧩 Components
Components are **Data Objects**.
* They inherit from a base `Component` class.
* They are stored using `std::shared_ptr` to allow polymorphic access (using `std::dynamic_pointer_cast`).

***Note:** Components are stored inside the Entity object, meaning memory is scattered (Heap), not contiguous.*

### ⚙️ Systems
Systems contain the **Game Logic**.
* **Execution:** A system does not store data. In its `update()`, it requests entities from the Manager.
* **Retrieval Strategy:** Systems currently iterate over **all** entities in the world and filter them dynamically:
    ```c++
    // Example: Logic inside a System
    for (auto& entity : ecs.getEntities()) {
        if (entity->getComponent<Position>() && entity->getComponent<Velocity>()) {
            // Update logic...
        }
    }
    ```

---

## 2. Execution Flow (The Game Loop)

The systems are executed sequentially in the order they were added to the `EcsManager` during initialization.

**Typical Frame Execution:**
1.  **Poll Events:** (Client Only) - InputSystem reads keyboard/network.
2.  **Logic & Physics:**
    * `VelocitySystem`: Updates position based on speed.
    * `CollisionSystem`: Checks AABB overlaps.
    * `ShootSystem`: Spawns projectiles.
3.  **Animation:** Updates sprite rects.
4.  **Render:** (Client Only) - Draws everything to the SFML window.

---

## 3. Network Architecture

The game uses an **Authoritative Server** model with a "Dumb Client".

### 🖥️ The Server
* **Role:** The brain of the game.
* **ECS Configuration:** Runs **all** logic systems (Movement, Collision, Health, Shooting).
* **Authority:** It calculates the result of every action. It does not trust the client.
* **Output:** It broadcasts the position and state of entities via UDP to all connected clients.

### 🎮 The Client
* **Role:** The visualizer.
* **ECS Configuration:** Runs a subset of systems (mostly Rendering and Input).
* **Input:** It sends raw inputs (Key Presses) to the server.
* **State:** It receives entity positions from the Server and updates its local components to match. It does **not** calculate physics locally (no prediction currently implemented).

### Communication Flow
1.  **Client** sends `INPUT` packet (UDP) -> **Server**.
2.  **Server** processes input -> Updates Physics/Game State.
3.  **Server** broadcasts `STATE_UPDATE` packet (UDP) -> **Client**.
4.  **Client** updates local Entity components -> Renders frame.

---

## 4. Memory & Performance Notes

* **Pointers:** Heavy usage of `std::shared_ptr` ensures memory safety and automatic deallocation when entities are destroyed.
* **RTTI:** The engine relies on `std::dynamic_pointer_cast` to retrieve components. While safer, this introduces a small runtime overhead compared to static casting or bitmasking.