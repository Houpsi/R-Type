/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ASystem
*/
#include "ASystem.hpp"

namespace ecs
{
	void ASystem::pushEntity(ecs::Entity newEntity)
	{
		_entity.push_back(newEntity);
	}
}
