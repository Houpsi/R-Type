/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ASystem
*/
#include "ASystem.hpp"
#include <algorithm>

namespace ecs
{
    ecs::Signature ASystem::getSignature()
	{
		return _targetSignature;
	}

    void ASystem::addEntity(ecs::Entity entity)
    {
        _entities.push_back(entity);
    }

    void ASystem::removeEntity(ecs::Entity entity)
    {
        auto it = std::find(_entities.begin(), _entities.end(), entity);

        if (it == _entities.end()) {
            return;
        }
        *it = _entities.back();
        _entities.pop_back();
    }
}
