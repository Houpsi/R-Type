/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#ifndef BOOTSTRAP_RENDERSYSTEM_HPP
    #define BOOTSTRAP_RENDERSYSTEM_HPP
#include "systems/system/ASystem.hpp"
#include "managers/EcsManager.hpp"
#include "components/inputPlayer/InputPlayer.hpp"
#include "components/position/Position.hpp"
#include "components/sprite/Sprite.hpp"
#include "SFML/Graphics.hpp"

namespace ecs {
    class RenderSystem : public ASystem
    {
    public:
        explicit RenderSystem(sf::RenderWindow &window) : _window(window) {};
        ~RenderSystem() override = default;
        void update(EcsManager &ecs) override;
        void configure(EcsManager &ecs) override;

    private:
        sf::RenderWindow &_window;
    };
}

#endif //BOOTSTRAP_RENDERSYSTEM_HPP