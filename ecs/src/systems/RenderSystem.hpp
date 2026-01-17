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
#include <map>

namespace ecs {
    enum class AccessibilityFilter : uint8_t {
        None = 0,
        HighContrast,
        Invert,
        Protanopia,
    };

    class RenderSystem : public System{
    public:
        explicit RenderSystem(sf::RenderWindow& window, const std::string& nameShader);
        void update(EcsManager &ecs);

    private:
        sf::RenderWindow& _window;
        sf::Shader _shader;
        bool _useFilter = true;
        AccessibilityFilter _currentFilter = AccessibilityFilter::None;
        std::map<AccessibilityFilter, sf::Shader> _shaders;


        void _loadShader(AccessibilityFilter type, const std::string& fragmentCode);
        AccessibilityFilter _getFilterByName(const std::string& name);
    };
}

#endif //BOOTSTRAP_RENDERSYSTEM_HPP