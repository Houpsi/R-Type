//
// Created by aleks on 27/11/2025.
//

#ifndef BOOTSTRAP_RENDERSYSTEM_HPP
#define BOOTSTRAP_RENDERSYSTEM_HPP


#include "System.hpp"
#include "GameEngine/EcsManager.hpp"
#include "GameEngine/Components/Position.hpp"
#include "GameEngine/Components/Sprite.hpp"
#include "SFML/Graphics.hpp"


class RenderSystem : public System
{
    public:
        explicit RenderSystem(sf::RenderWindow &window) : _window(window) {};
        ~RenderSystem() override = default;
        void update(EcsManager &ecs) override;
    private:
        sf::RenderWindow &_window;
};


#endif //BOOTSTRAP_RENDERSYSTEM_HPP