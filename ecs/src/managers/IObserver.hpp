/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Observer
*/

#ifndef R_TYPE_CLIENT_IOBSERVER_HPP
	#define R_TYPE_CLIENT_IOBSERVER_HPP
#include "Constants.hpp"

namespace ecs
{
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void onSignatureChanged(ecs::Entity entity,	const std::bitset<cmn::NB_COMPONENTS> &signature) = 0;

	};
} // ecs

#endif //R_TYPE_CLIENT_IOBSERVER_HPP