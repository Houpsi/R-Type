/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ASystem
*/

#ifndef R_TYPE_CLIENT_ASYSTEM_HPP
	#define R_TYPE_CLIENT_ASYSTEM_HPP
#include "ISystem.hpp"
#include "managers/EcsManager.hpp"

namespace ecs
{
	class EcsManager;

	class ASystem: public ISystem
	{
	public:
		virtual ~ASystem() = default;

		virtual void update(ecs::EcsManager &ecs) = 0;
		void pushEntity(ecs::Entity) override;

	protected:
		std::vector<ecs::Entity> _entity;
	};
}

#endif //R_TYPE_CLIENT_ASYSTEM_HPP