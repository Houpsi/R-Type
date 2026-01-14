/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#include "HealthSystem.hpp"

namespace ecs
{
	void HealthSystem::update(EcsManager& ecs)
	{
		for (const auto& entity : _entities)
		{
			auto health = ecs.getComponent<Health>(entity).getHealth();
			if (health <= 0) {
				ecs.addComponentToEntity<Destroy>(entity, {});
			}
		}
	}

    void HealthSystem::configure(EcsManager &ecs)
    {
        _targetSignature.set(ecs.getComponentType<Health>());
    }
} // ecs