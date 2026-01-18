/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Text
*/

#include "Text.hpp"

namespace ecs
{
    Text::Text(const sf::Font& font, unsigned int size, sf::Color color)
    : _text(font, "", size)
    {
        _text.setFillColor(color);
    }

    sf::Text& Text::getText()
    {
        return _text;
    }

    const sf::Text& Text::getText() const
    {
        return _text;
    }

    void Text::setString(const std::string& str)
    {
        _text.setString(str);
    }
} // ecs