#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Floor {
public:
	Floor(); // default constructor to set initial values
	void createFloor(sf::VertexArray& rVA, sf::Vector2f resolution);

	sf::Texture getTexture();

protected:

private:
	TextureHolder th; // brings in TextureHolder class
	sf::Vector2f m_Resolution; // holds resolution of screen
};