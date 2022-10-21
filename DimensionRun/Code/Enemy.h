#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"
#ifndef ENEMY_H
#define ENEMY_H

using namespace sf;

class Enemy {
public:
	Enemy();

	void spawn(Vector2f resolution, float elapsedTime);
	void moveTextureRect();
	void setSpriteFromSheet(IntRect textureBox);
	void update();

	FloatRect getPosition();
	Sprite getSprite();

private:
	const float INITIAL_HEALTH = 100;
	const float INITIAL_SPEED = 50;

	Sprite m_Sprite;

	Vector2f m_Resolution;

	int m_Health;
	float m_Speed;

	Vector2f m_Position;

	TextureHolder th;

	Vector2i sheetCoordinate;
	Vector2i spriteSize;

	int animation_it_limit;
	int ani_counter{};
	float timeElapsed;
	Clock clock;
	float animationTimer = 0;
};
#endif
