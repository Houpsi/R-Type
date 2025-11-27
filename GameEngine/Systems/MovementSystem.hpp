//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_MOVEMENTSYSTEM_HPP
#define BOOTSTRAP_MOVEMENTSYSTEM_HPP
#include <memory>
#include <vector>

#include "System.hpp"


#include "../Entity.hpp"
class MovementSystem : public System {
    private:
    float _movementSpeed;
    public:
    explicit MovementSystem(float test): _movementSpeed(test) {};
    ~MovementSystem() = default;
    void update(EcsManager &ecs) override;
};


#endif //BOOTSTRAP_MOVEMENTSYSTEM_HPP