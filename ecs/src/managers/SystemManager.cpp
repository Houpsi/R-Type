/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ecs
{
	void SystemManager::onSignatureChanged(ecs::Entity entity, std::bitset<cmn::NB_COMPONENTS>& signature)
	{
		for (auto &[_, system]: _systems)
		{
			auto oldSignature = system.getSignature();
			if ((oldSignature & signature) == signature)
			{
				// need to change the signature
			}
		}
	}
}
