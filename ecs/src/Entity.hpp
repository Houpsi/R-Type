/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Entity
*/

#ifndef BOOTSTRAP_ENTITY_HPP
    #define BOOTSTRAP_ENTITY_HPP
#include "Component.hpp"
#include <memory>
#include <vector>

namespace ecs {
class Entity {
  public:
    Entity() = default;
    ~Entity() = default;

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
    size_t _id;

  private:
    std::vector<std::shared_ptr<Component>> _components;

};
}

#endif //BOOTSTRAP_ENTITY_HPP