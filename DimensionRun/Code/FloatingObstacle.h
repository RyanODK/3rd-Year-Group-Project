#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"
#ifndef FLOATINGOBSTACLE_H
#define FLOATINGOBSTACLE_H

using namespace sf;

class FloatingObstacle {
public:
	FloatingObstacle(); // default constructor to set initial values

	void spawn(Vector2f resolution); // spawns player in game and saves resolution and elapsedTime for future use
	void update(float elapsedTime); // updates player animation and movement
	void moveTextureRect(float elapsedTime); // this will move the IntRect around the texture for player in order to create an animation
	void setSpriteFromSheet(IntRect textureBox); // this sets a IntRect around the needed frames from sprite sheet

	Sprite getSprite(); // returns sprite
	FloatRect getPosition(); // returns global bounds position of player spritegetGlobal()
	FloatRect getGlobal();

protected:

	Sprite m_Sprite; // sprite of player

	Vector2i sheetCoordinate; // holds coordinates of sprite sheet
	Vector2i spriteSize; // holds size of sprite

private:
	int obstacleSpeed;
	bool obstacleActive = false;

	Vector2f m_Position; // holds position of sprite

	TextureHolder th; // brings in TextureHolder class

	Vector2f m_Resolution; // holds resolution of screen
};
#endif


