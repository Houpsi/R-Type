/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ecs
{
	void SystemManager::onSignatureChanged(Entity entity, const std::bitset<cmn::NB_COMPONENTS>& signature)
	{
		for (auto &system: _systems)
		{
			auto targetSignature = system.getSignature();
			if ((targetSignature & signature) == signature) {
				system.setEntity(entity);
			}
		}
	}

	void SystemManager::addSystem(std::shared_ptr<ASystem> system) {
		_systems.push_back(std::move(system));
	}
}
