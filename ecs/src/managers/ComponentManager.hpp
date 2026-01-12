/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ComponentManager
*/

#ifndef R_TYPE_COMPONENTMANAGER_HPP
#define R_TYPE_COMPONENTMANAGER_HPP
#include "Constants.hpp"
#include "components/IComponentArray.hpp"
#include "components/ComponentArray.hpp"
#include <type_traits>
#include <typeindex>

namespace ecs {
    class ComponentManager {
    public:
        template <typename T>
        void registerComponentType()
        {
            std::type_index index = std::type_index(typeid(T));

            if (_componentArrays.find(index) != _componentArrays.end()) {
                return;
            }

            _componentArrays[index] = std::make_shared<ComponentArray<T>>();
        }

        template <typename T>
        void addComponent(Entity entity, T comp)
        {
            getComponentArray<T>()->insert(entity, comp);
        }

        template <typename T>
        void removeComponent(Entity entity)
        {
            getComponentArray<T>()->remove(entity);
        }

        template <typename T>
        T& getComponent(Entity entity)
        {
            return getComponentArray<T>()->get(entity);
        }

        void entityDestroyed(Entity entity)
        {
            for (auto const &pair : _componentArrays) {
                auto const &component = pair.second;
                component->entityDestroyed(entity);
            }
        }
    private:
        template <typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            std::type_index index = std::type_index(typeid(T));

            if (_componentArrays.find(index) == _componentArrays.end()) {
                throw std::runtime_error("Component not registered before use.");
            }
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[index]);
        }

        std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> _componentArrays;
    };
}


#endif //R_TYPE_COMPONENTMANAGER_HPP
