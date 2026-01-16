/*
** EPITECH PROJECT, 2026
** r-type_client
** File description:
** Score
*/

#ifndef R_TYPE_CLIENT_SCORE_HPP
	#define R_TYPE_CLIENT_SCORE_HPP
#include <string>
#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace ecs
{
	class Score: public Component {
	public:
		Score(): _score(0) {};
		void addToScore(int v) { _score += v; }
		void setScore(int v) { _score = v; }
		int getScore() const { return _score; }

	private:
		int _score = 0;
	};

	class Text: public Component {
	public:
		Text(const sf::Font& font,
		 unsigned int size = 24,
		 sf::Color color = sf::Color::White)
		: _text(font, "", size)
		{
					_text.setFillColor(color);
		}

		sf::Text& getText() { return _text; }
		const sf::Text& getText() const { return _text; }

		void setString(const std::string& str) { _text.setString(str); }

	private:
		sf::Text _text;
	};
} // ecs

#endif //R_TYPE_CLIENT_SCORE_HPP