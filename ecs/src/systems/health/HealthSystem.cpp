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
		for (const auto& entity : ecs.getEntitiesWithComponent<Health>())
		{
			auto health = entity->getComponent<Health>()->getHealth();
			if (health <= 0)
			{
				entity->addComponent<Destroy>();
			}
		}
	}
} // ecs