#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/*
	THIS CODE WAS CREATED BY Raimondas Pupius FROM THE BOOK SFML GAME DEVELOPMENT BY EXAMPLE
*/

enum class GUI_ElementState { Neutral, Focused, Clicked };

struct GUI_Style {
	GUI_Style() : m_textSize(12), m_textCenterOrigin(false),
		m_backgroundImageColor(255, 255, 255, 255)
	{
		sf::Color none = sf::Color(0, 0, 0, 0);
		m_backgroundColor = none;
		m_elementColor = none;
		m_textColor = none;
	}

	sf::Vector2f m_size; // Element size.
	// Background properties.
	sf::Color m_backgroundColor;
	sf::Color m_elementColor;
	std::string m_backgroundImage;
	sf::Color m_backgroundImageColor;
	// Text properties.
	sf::Color m_textColor;
	std::string m_textFont;
	sf::Vector2f m_textPadding;
	unsigned int m_textSize;
	bool m_textCenterOrigin;
	// Glyph properties.
	std::string m_glyph;
	sf::Vector2f m_glyphPadding;
};

struct GUI_Visual {
	sf::RectangleShape m_backgroundSolid;
	sf::Sprite m_backgroundImage;
	sf::Sprite m_glyph;
	sf::Text m_text;
};