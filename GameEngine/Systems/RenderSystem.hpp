//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_RENDERSYSTEM_HPP
#define BOOTSTRAP_RENDERSYSTEM_HPP
#include "System.hpp"
#include "SFML/Graphics.hpp"


class RenderSystem : public System {
    private:
    sf::RenderWindow &_window;
    public:
    explicit RenderSystem(sf::RenderWindow &window) : _window(window) {};
    ~RenderSystem() override = default;

    void update(EcsManager &ecs) override {
        _window.clear(sf::Color::Black);
    }

};


#endif //BOOTSTRAP_RENDERSYSTEM_HPP