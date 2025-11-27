//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_SYSTEM_HPP
#define BOOTSTRAP_SYSTEM_HPP
#include <memory>
#include <vector>



class Entity;
class EcsManager; // <- forward declaration

class System {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void update(EcsManager &ecs) = 0;
};


#endif //BOOTSTRAP_SYSTEM_HPP