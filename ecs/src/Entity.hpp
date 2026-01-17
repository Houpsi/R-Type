/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Entity
*/

#ifndef BOOTSTRAP_ENTITY_HPP
    #define BOOTSTRAP_ENTITY_HPP
#include "components/Component.hpp"
#include <memory>
#include <vector>
#include <algorithm>

namespace ecs {
class Entity {
  public:
    explicit Entity(uint32_t id) : _id(id) {};
    ~Entity() = default;
    [[nodiscard]] uint32_t getId() const;
    template <typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        _components.push_back(component);
        return component;
    }
    template <typename T>
    std::shared_ptr<T> addComponent() {
        auto component = std::make_shared<T>();
        _components.push_back(component);
        return component;
    }
    template <typename T>
    std::shared_ptr<T> getComponent() {
        for (const auto& component : _components) {
            if (std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(component)) {
                return casted;
            }
        }
        return nullptr;
    }

    template <typename T>
    void removeComponent() {
        _components.erase(
            std::remove_if(_components.begin(), _components.end(),
                [](const std::shared_ptr<Component>& c) {
                    return std::dynamic_pointer_cast<T>(c) != nullptr;
                }),
            _components.end()
        );
    }


  private:
    std::vector<std::shared_ptr<Component>> _components;
    uint32_t _id;

};
}

#endif //BOOTSTRAP_ENTITY_HPP