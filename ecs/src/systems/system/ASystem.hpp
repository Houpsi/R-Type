/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** ASystem
*/

#ifndef R_TYPE_CLIENT_ASYSTEM_HPP
	#define R_TYPE_CLIENT_ASYSTEM_HPP
#include "ISystem.hpp"
#include "managers/EntityManager.hpp"

namespace ecs
{
	class EcsManager;

	class ASystem : public ISystem
	{
	public:
		virtual ~ASystem() = default;

		virtual void update(ecs::EcsManager &ecs) = 0;
		virtual void configure(ecs::EcsManager &ecs) = 0;
		Signature getSignature() override;
        void addEntity(ecs::Entity entity) override;
        void removeEntity(ecs::Entity entity) override;

	protected:
		std::vector<ecs::Entity> _entities;
        ecs::Signature _targetSignature;
	};
}

#endif //R_TYPE_CLIENT_ASYSTEM_HPP