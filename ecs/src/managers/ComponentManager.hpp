/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** ComponentManager
*/

#ifndef R_TYPE_COMPONENTMANAGER_HPP
#define R_TYPE_COMPONENTMANAGER_HPP
#include "src/constants/GameConstants.hpp"
#include "components/IComponentArray.hpp"
#include "components/ComponentArray.hpp"
#include <type_traits>
#include <typeindex>
#include <memory>

namespace ecs {
    class ComponentManager {
    public:
        template <typename T>
        void registerComponentType()
        {
            std::type_index index = std::type_index(typeid(T));

            if (_componentArrays.contains(index)) {
                return;
            }

            _componentBits[index] = _nextBitId;
            _nextBitId++;
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

        template<typename T>
        uint8_t getComponentBitId()
        {
            std::type_index index = std::type_index(typeid(T));

            if (!_componentArrays.contains(index)) {
                throw std::runtime_error("Component not registered before use.");
            }
            return _componentBits[index];
        }

    private:
        template <typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            std::type_index index = std::type_index(typeid(T));

            if (!_componentArrays.contains(index)) {
                throw std::runtime_error("Component not registered before use.");
            }
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[index]);
        }

        std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> _componentArrays;

        std::unordered_map<std::type_index, uint8_t> _componentBits;
        uint8_t _nextBitId = 0;
    };
}


#endif //R_TYPE_COMPONENTMANAGER_HPP
