#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"
#ifndef ENEMY_H
#define ENEMY_H

using namespace sf;

class Enemy {
public:
	void spawn(Vector2f startPosition, Vector2f scale); // spawns enemy taking in desired position and scale
	void moveTextureRect(double frameTime); // moves texture rect to execute animation 
	void setSpriteFromSheet(IntRect textureBox, Vector2i size); // sets texture for sprite from enemy sprite sheet
	void update(float elapsedTime); // takes in elapsedtime to use in class for now

	FloatRect getPosition(); // gets position of sprite
	Sprite getSprite(); // returns sprite

private:
	const float INITIAL_HEALTH = 100;
	const float INITIAL_SPEED = 50;

	int m_Health;
	float m_Speed;

	Vector2f m_Position;
	Vector2f resetPosition;

	TextureHolder th; // texture holder class 

protected:
	Sprite m_Sprite; 

	Vector2i sheetCoordinate;
	Vector2i spriteSize;

	int animation_it_limit;
	int ani_counter{};
	float timeElapsed;
	float animationTimer = 0;
	
	Vector2f m_Resolution;

	bool EnemyActive = false;
};
#endif
