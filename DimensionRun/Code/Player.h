#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef PLAYER_H
#define PLAYER_H

using namespace sf;

class Player {
public:
	Player();

	void spawn(Vector2f resolution);
	void updateAnimation(Clock& clock);
	FloatRect getPosition();
	Sprite getSprite();
	void updateMovement();

	// movement functions
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// stop player moving in certain direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

private:
	const float INITIAL_HEALTH = 100;
	const float INITIAL_SPEED = 50;

	Sprite m_Sprite;

	Texture m_Texture;

	Vector2f m_Resolution;

	int m_Health;
	float m_Speed;

	IntRect m_playerRect;
	Vector2f m_Position;

	// direction of player
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
};
#endif
