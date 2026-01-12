/*
** EPITECH PROJECT, 2026
** R_Type
** File description:
** ComponentArray
*/

#ifndef R_TYPE_COMPONENTARRAY_HPP
#define R_TYPE_COMPONENTARRAY_HPP

#include "components/IComponentArray.hpp"
#include <unordered_map>

namespace ecs {
    template <typename T>
    class ComponentArray : public IComponentArray {
    public:
        void insert(Entity entity, T component)
        {
            if (_entityToIndex.find(entity) != _entityToIndex.end()) {
                _denseArray[_entityToIndex[entity]] = component;
                return;
            }

            std::size_t newIndex = _denseArray.size();
            _entityToIndex[entity] = newIndex;
            _indexToEntity[newIndex] = entity;
            _denseArray.push_back(component);
        }

        void remove(Entity entity)
        {
            if (_entityToIndex.find(entity) == _entityToIndex.end()) {
                return;
            }
            size_t indexOfRemovedEntity = _entityToIndex[entity];
            size_t indexOfLastElement   = _denseArray.size() - 1;
            Entity entityOfLastElement = _indexToEntity[indexOfLastElement];

            _denseArray[indexOfRemovedEntity] = _denseArray[indexOfLastElement];

            _entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
            _indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

            _entityToIndex.erase(entity);
            _indexToEntity.erase(indexOfLastElement);
            _denseArray.pop_back();
        }

        T& get(Entity entity)
        {
            if (_entityToIndex.find(entity) == _entityToIndex.end()) {
                throw std::runtime_error("Component getter failed: Entity does not possess this component.");
            }
            return _denseArray[_entityToIndex[entity]];
        }

        void entityDestroyed(Entity entity) override
        {
            if (_entityToIndex.find(entity) != _entityToIndex.end()) {
                remove(entity);
            }
        }
    private:
        std::vector<T> _denseArray;
        std::unordered_map<Entity, std::size_t> _entityToIndex;
        std::unordered_map<std::size_t, Entity> _indexToEntity;
    };
}


#endif //R_TYPE_COMPONENTARRAY_HPP
