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
		for (const auto& entity : _entity)
		{
			auto health = ecs.getComponentManager()<Health>->get(entity)->getHealth();
			if (health <= 0)
			{
				ecs.getComponentManager()<Health>->addComponent<Destroy>();
				// entity->addComponent<Destroy>();
			}
		}
	}
} // ecs