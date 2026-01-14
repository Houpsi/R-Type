/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ecs
{
	void SystemManager::onSignatureChanged(ecs::Entity entity, const ecs::Signature &signature)
	{
		for (auto &pair : _systems) {
            auto const &system = pair.second;
			auto targetSignature = system->getSignature();
			if ((signature & targetSignature) == targetSignature) {
                system->addEntity(entity);
			} else {
                system->removeEntity(entity);
            }
		}
	}
}
