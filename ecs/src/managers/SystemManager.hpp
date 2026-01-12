/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SystemManager
*/

#ifndef R_TYPE_SYSTEMMANAGER_HPP
	#define R_TYPE_SYSTEMMANAGER_HPP
#include "EntityManager.hpp"
#include "IObserver.hpp"
#include <memory>

namespace ecs
{
	class ASystem;

	class SystemManager : public ecs::IObserver {
	public:
		// to call in the function addComponent
		void onSignatureChanged(Entity entity, const std::bitset<cmn::NB_COMPONENTS>& signature) override;
		void addSystem(std::shared_ptr<ASystem> system);

		private:
			std::vector<std::shared_ptr<ASystem>> _systems;
	};
}


#endif //R_TYPE_SYSTEMMANAGER_HPP
