//
// Created by aleks on 27/11/2025.
//

#include "MovementSystem.hpp"

#include <iostream>
#include <ostream>

#include "../EcsManager.hpp"
#include "../Components/Health.hpp"
#include "../Components/Position.hpp"

void MovementSystem::update(EcsManager &ecs) {
    for (auto entity : ecs.getEntitiesWithComponent<Health>()) {
        auto pos = entity->getComponent<Position>();
    }
}
