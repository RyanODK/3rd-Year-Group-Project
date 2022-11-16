#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"

class FloatingObstacle {
public:
	FloatingObstacle(); // default constructor to set initial values

	//void spawn(Vector2f resolution); // spawns player in game and saves resolution and elapsedTime for future use
	void spawn(sf::Vector2f startPosition, sf::Vector2f scale);
	void update(float elapsedTime); // updates player animation and movement
	void moveTextureRect(float elapsedTime); // this will move the IntRect around the texture for player in order to create an animation
	void setSpriteFromSheet(sf::IntRect textureBox); // this sets a IntRect around the needed frames from sprite sheet

	sf::Sprite getSprite(); // returns sprite
	sf::FloatRect getPosition(); // returns global bounds position of player spritegetGlobal()
	sf::FloatRect getGlobal();

protected:

	sf::Sprite m_Sprite; // sprite of player

	sf::Vector2i sheetCoordinate; // holds coordinates of sprite sheet
	sf::Vector2i spriteSize; // holds size of sprite

private:
	int obstacleSpeed;
	bool obstacleActive = false;

	sf::Vector2f m_Position; // holds position of sprite
	sf::Vector2f resetPosition;

	TextureHolder th; // brings in TextureHolder class

	sf::Vector2f m_Resolution; // holds resolution of screen
};


