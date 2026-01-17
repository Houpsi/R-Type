/*
** EPITECH PROJECT, 2025
** r-type_client
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

namespace ecs {
    const std::string highContrastShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        float gray = dot(pixel.rgb, vec3(0.299, 0.587, 0.114));
        float contrast = step(0.4, gray);
        gl_FragColor = vec4(contrast, contrast, contrast, pixel.a);
    }
    )";
    const std::string invertShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        gl_FragColor = vec4(1.0 - pixel.r, 1.0 - pixel.g, 1.0 - pixel.b, pixel.a);
    }
    )";
    const std::string protanopiaShader = R"(
    uniform sampler2D texture;
    void main() {
        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        mat3 matrix = mat3(
            0.567, 0.433, 0.0,
            0.558, 0.442, 0.0,
            0.0,   0.242, 0.758
        );
        vec3 color = pixel.rgb * matrix;
        gl_FragColor = vec4(color, pixel.a);
    }
)";

    RenderSystem::RenderSystem(sf::RenderWindow &window, const std::string &nameShader) : _window(window)
    {
        AccessibilityFilter const type = _getFilterByName(nameShader);
        if (type != AccessibilityFilter::None) {
            _loadShader(type, highContrastShader);
            _currentFilter = type;
            std::cout << "[RenderSystem] Accessibility " <<  nameShader << "shaders loaded." << std::endl;
            return;
        }
    }

    void RenderSystem::_loadShader(AccessibilityFilter type, const std::string& fragmentCode) {
        if (!_shaders[type].loadFromMemory(fragmentCode, sf::Shader::Type::Fragment)) {
            std::cerr << "[Error] Failed to compile shader type " << (int)type << std::endl;
        } else {
            _shaders[type].setUniform("texture", sf::Shader::CurrentTexture);
        }
    }

    AccessibilityFilter RenderSystem::_getFilterByName(const std::string& name) {
        static const std::map<std::string, AccessibilityFilter> filterMap = {
            {"normal",        AccessibilityFilter::None},
            {"high_contrast", AccessibilityFilter::HighContrast},
            {"invert",        AccessibilityFilter::Invert},
            {"protanopia",    AccessibilityFilter::Protanopia}
        };
        auto it = filterMap.find(name);
        if (it != filterMap.end()) {
            return it->second;
        }
        return AccessibilityFilter::None;
    }

    void RenderSystem::update(EcsManager &ecs)
    {
        _window.clear(sf::Color::Black);
        const auto entities = ecs.getEntities();

        sf::RenderStates states;
        if (_currentFilter != AccessibilityFilter::None) {
            states.shader = &_shaders[_currentFilter];
        }

        for (const auto& entity : entities) {
            auto spriteComp = entity->getComponent<Sprite>();
            auto positionComp = entity->getComponent<Position>();
            auto textComp = entity->getComponent<Text>();
            auto scoreComp = entity->getComponent<Score>();

            if (spriteComp) {
                auto sprite = spriteComp->getSprite();
                if (positionComp) {
                    sprite.setPosition({positionComp->getX(), positionComp->getY()});
                }
                _window.draw(sprite, states);
            }
            if (textComp) {
                auto& t = textComp->getText();
                if (positionComp)
                    t.setPosition({positionComp->getX(), positionComp->getY()});
                if (scoreComp) {
                    t.setString("Score: " + std::to_string(scoreComp->getScore()));
                }
                _window.draw(t);
            }
        }
        _window.display();
    }


} // namespace ECS
