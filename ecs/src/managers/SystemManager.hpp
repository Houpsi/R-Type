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

namespace ecs
{
	class SystemManager : public ecs::IObserver {
	public:
		void onSignatureChanged(ecs::Entity entity, const std::bitset<cmn::NB_COMPONENTS>& signature) override;
		// to call in the function addComponent


	};
}


#endif //R_TYPE_SYSTEMMANAGER_HPP
