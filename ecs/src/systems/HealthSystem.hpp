/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** Health
*/

#ifndef R_TYPE_CLIENT_HEALTH_HPP
	#define R_TYPE_CLIENT_HEALTH_HPP
#include "System.hpp"
#include "EcsManager.hpp"
#include "components/Health.hpp"
#include "components/Destroy.hpp"


namespace ecs
{
	class HealthSystem : public System
	{
		public:
			HealthSystem() = default;
			void update(EcsManager &ecs) override;
	};
} // ecs

#endif //R_TYPE_CLIENT_HEALTH_HPP