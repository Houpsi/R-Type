/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#ifndef R_TYPE_CLIENT_HEALTH_HPP
	#define R_TYPE_CLIENT_HEALTH_HPP
#include "systems/system/ASystem.hpp"
#include "managers/EcsManager.hpp"
#include "components/health/Health.hpp"
#include "components/destroy/Destroy.hpp"

namespace ecs
{
	class HealthSystem : public ASystem
	{
		public:
			HealthSystem() = default;
			void update(EcsManager &ecs) override;
            void configure(EcsManager &ecs) override;
	};
} // ecs

#endif //R_TYPE_CLIENT_HEALTH_HPP