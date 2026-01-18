/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Text
*/

#ifndef R_TYPE_CLIENT_TEXT_HPP
#define R_TYPE_CLIENT_TEXT_HPP
#include "Component.hpp"
#include <string>
#include <SFML/Graphics.hpp>

namespace ecs
{
    class Text: public Component {
    public:
        Text(const sf::Font& font,
         unsigned int size = 24,
         sf::Color color = sf::Color::White);

        sf::Text& getText();
        const sf::Text& getText() const;
        void setString(const std::string& str);

    private:
        sf::Text _text;
    };
} // ecs

#endif //R_TYPE_CLIENT_TEXT_HPP