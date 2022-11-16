#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"

class Enemy {
public:
	void spawn(sf::Vector2f startPosition, sf::Vector2f scale); // spawns enemy taking in desired position and scale
	void moveTextureRect(double frameTime); // moves texture rect to execute animation 
	void setSpriteFromSheet(sf::IntRect textureBox, sf::Vector2i size); // sets texture for sprite from enemy sprite sheet
	void update(float elapsedTime, float velocity); // takes in elapsedtime to use in class for now
	void setAttack(bool attack);

	sf::FloatRect getPosition(); // gets position of sprite
	sf::Sprite getSprite(); // returns sprite

private:
	const float INITIAL_HEALTH = 100;
	const float INITIAL_SPEED = 50;

	int m_Health;
	float m_Speed;

	sf::Vector2f m_Position;
	sf::Vector2f resetPosition;

	TextureHolder th; // texture holder class 

protected:
	sf::Sprite m_Sprite;

	sf::Vector2i sheetCoordinate;
	sf::Vector2i spriteSize;

	int animation_it_limit;
	int ani_counter{};
	float timeElapsed;
	float animationTimer = 0;
	
	sf::Vector2f m_Resolution;

	bool EnemyActive = false;
	bool EnemyAttack = false;
};
