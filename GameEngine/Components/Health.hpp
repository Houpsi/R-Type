//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_HEALTH_HPP
#define BOOTSTRAP_HEALTH_HPP
#include "Component.hpp"


class Health : public Component {
    private:
        int _health = 0;
    public:
    Health(int const health) : _health(health) {};
    ~Health() = default;
    int getHealth() const;
    void setHealth(int const health);
};


#endif //BOOTSTRAP_HEALTH_HPP