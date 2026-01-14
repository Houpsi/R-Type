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
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "systems/system/ASystem.hpp"

namespace ecs
{
    class ASystem;

	class SystemManager : public ecs::IObserver {
	public:
		void onSignatureChanged(Entity entity, const Signature& signature) override;
        // TODO entityDestroyed -> pour enlever tous les entity dans le cache des systems
        template <typename T>
        void addSystem(ecs::EcsManager &ecsManager)
        {
            auto system = std::make_shared<T>();
            _systems[std::type_index(typeid(T))] = system;
            system->configure(ecsManager);
        }

		template <typename T, typename... Args>
		void addSystem(ecs::EcsManager &ecsManager, Args&&... args)
        {
            auto system = std::make_shared<T>(std::forward<Args>(args)...);
            _systems[std::type_index(typeid(T))] = system;
            system->configure(ecsManager);
        }

		void updateSystems(ecs::EcsManager &ecsManager)
        {
        	for (auto &[_, system] : _systems) {
        		system->update(ecsManager);
        	}
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<ASystem>> _systems;
	};
}


#endif //R_TYPE_SYSTEMMANAGER_HPP
