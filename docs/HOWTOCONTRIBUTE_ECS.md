# Contributing to the ECS Library

This document outlines the architectural standards and coding conventions for the **Entity-Component-System (ECS)** library.
Because the ECS is the core engine of the R-Type project, strict adherence to these rules is required to ensure performance, stability, and maintainability.

---

## 1. Architecture

Our ECS follows a **Strict Separation of Data and Logic**:
* **Components**: Pure data holders. They store state but contain **NO** game logic.
* **Systems**: The logic processors. They iterate over entities and modify components.
* **Entities**: ID containers that group components together.

---

## 2. Creating New Components

### Rules
1.  **Inheritance**: All components **MUST** inherit from the base class `Component`.
2.  **No Logic**: Components must not contain game logic (e.g., no `update()`, `move()`, or `takeDamage()` methods). They only provide **Getters** and **Setters**.
3.  **File Splitting**: You **MUST** separate declaration (`.hpp`) and implementation (`.cpp`), even if the component is small.
4.  **Naming**:
    * Files: `PascalCase.hpp` (e.g., `Health.hpp`)
    * Private members: Prefix with an underscore `_` (e.g., `_health`).

### Template

**Health.hpp**
```cpp
#ifndef HEALTH_HPP
#define HEALTH_HPP

#include "Component.hpp"

namespace ecs {
    class Health : public Component {
        public:
            explicit Health(int hp);
            ~Health() override = default;

            int getHealth() const;
            void setHealth(int hp);

        private:
            int _health; // Private member style
    };
}
#endif
```

**Health.cpp**
```cpp
#include "Health.hpp"

namespace ecs {
    Health::Health(int hp) : _health(hp) {}

    int Health::getHealth() const
    {
        return _health;
    }

    void Health::setHealth(int hp)
    {
        _health = hp;
    }
}
```

---

## 3. Creating New Systems

### Rules

1. **Inheritance**: All systems **MUST** inherit from the base class `System`.

2. **Signature**: You must implement the pure virtual method:
    ```cpp
    void update(EcsManager &ecs) override;
    ```

3. **Entity Retrieval:** You can retrieve entities in two ways:
    **Iteration**: Loop through all entities and check if (entity->hasComponent<T>()).
    **Filtering**: Use ecs.getEntitiesWithComponent<T>() for a filtered list.


### Template

**MovementSystem.cpp**
```cpp
void MovementSystem::update(EcsManager &ecs) {
    for (auto &entity : ecs.getEntities()) {
        auto pos = entity->getComponent<Position>();
        auto vel = entity->getComponent<Velocity>();

        if (pos && vel) {
            // LOGIC GOES HERE, NOT IN THE COMPONENT
            pos->setX(pos->getX() + vel->getX() * ecs.getDeltaTime());
        }
    }
}
```

---

## 4. Resource Management

**Never load assets manually.** Raw calls to `sf::Texture::loadFromFile` inside components or systems are **forbidden**.
You must use the `ResourceManager` provided by the `EcsManager`.

**Correct Usage:**
```cpp
// Inside Game.cpp or System logic
auto &manager = ecs.getResourceManager();
sf::Texture &texture = manager.getTexture("assets/sprites/player.png");

// Pass the reference to the component
entity->addComponent<Sprite>(texture);
```

---

## 5. Testing Policy

The ECS library is critical infrastructure. Therefore, testing is mandatory.

- Requirement: Every new Component must have a corresponding GTest suite in the tests/ folder.
- Filename: tests/Tests{ComponentName}.cpp

**Example Test:**
```c++
TEST(HealthTest, ConstructorSetsValue) {
    ecs::Health hp(100);
    EXPECT_EQ(hp.getHealth(), 100);
}
```

---

## 6. Pre-Commit Checklist

Before pushing your code, verify the following:

- File names are in PascalCase.
- Logic is strictly inside Systems, not Components.
- .hpp and .cpp are separated.
- Private variables start with _.
- No raw asset loading (used ResourceManager).
- Unit Tests added and passing (ctest).
- Code compiles with -Wall -Wextra -Werror (Clean CI).
