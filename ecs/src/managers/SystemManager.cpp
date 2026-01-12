/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ecs
{
	void SystemManager::onSignatureChanged(ecs::Entity entity, const std::bitset<cmn::NB_COMPONENTS>& signature)
	{
		for (auto &[_, system]: _systems)
		{
			auto targetSignature = system.getSignature();
			if ((targetSignature & signature) == signature)
			{
				system.setEntity(entity);
			}
		}
	}
}
