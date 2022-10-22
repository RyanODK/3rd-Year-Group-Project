#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"
#ifndef PLAYER_H
#define PLAYER_H

using namespace sf;

class Player {
public:
	Player(); // default constructor to set initial values

	void spawn(Vector2f resolution, float gravity); // spawns player in game and saves resolution and elapsedTime for future use
	void moveTextureRect(float elapsedTime); // this will move the IntRect around the texture for player in order to create an animation
	void setSpriteFromSheet(IntRect textureBox); // this sets a IntRect around the needed frames from sprite sheet
	void update(float elapsedTime); // updates player animation and movement

	Sprite getSprite(); // returns sprite
	FloatRect getPosition(); // returns global bounds position of player sprite

protected:
	const float INITIAL_HEALTH = 100; // sets initial health (placeholder)
	const float INITIAL_SPEED = 50; // sets initial speed (placeholder)

	Sprite m_Sprite; // sprite of player

	Vector2i sheetCoordinate; // holds coordinates of sprite sheet
	Vector2i spriteSize; // holds size of sprite

	int animation_it_limit; // holds limit of animation iterator
	int ani_counter{}; // holds animation counter
	float animationTimer = 0; // animation timer to check for switching frames of animation

private:
	float m_gravity;

	int m_Health;
	float m_Speed;

	Vector2f m_Position; // holds position of sprite

	TextureHolder th; // brings in TextureHolder class

	Vector2f m_Resolution; // holds resolution of screen
};
#endif
