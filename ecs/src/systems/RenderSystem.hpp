/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#ifndef BOOTSTRAP_RENDERSYSTEM_HPP
    #define BOOTSTRAP_RENDERSYSTEM_HPP
#include "System.hpp"
#include "../EcsManager.hpp"
#include "components/InputPlayer.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "SFML/Graphics.hpp"

namespace ecs {
class RenderSystem : public System
{
  public:
    explicit RenderSystem(sf::RenderWindow &window) : _window(window) {};
    ~RenderSystem() override = default;
    void update(EcsManager &ecs) override;
  private:
    sf::RenderWindow &_window;
};
}

#endif //BOOTSTRAP_RENDERSYSTEM_HPP