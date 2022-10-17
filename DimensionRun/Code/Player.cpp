#include "Player.h"

Player::Player() {
	m_Health = INITIAL_HEALTH;
	m_Speed = INITIAL_SPEED;

	// loading idle spritesheet
	m_Texture.loadFromFile("Graphics/Free 3 Cyberpunk Sprites Pixel Art/2 Punk/Idle/Punk_idle.png");
	m_playerRect.left = 0;
	m_playerRect.width = 48;
	m_playerRect.top = 0;
	m_playerRect.height = 48;
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setTextureRect(m_playerRect);
}

void Player::spawn(Vector2f resolution) {
	// depending on resolution set position and scale of player
	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
		m_Sprite.setPosition(250, 1080);
		m_Sprite.setScale(6, 6);
	}
	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
		m_Sprite.setPosition(200, 850);
		m_Sprite.setScale(4, 4);
	}

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::updateAnimation(Clock clock) {
	// every 0.25 seconds 
	// change playerSprite idle animation
	if (clock.getElapsedTime().asSeconds() > 0.25f) {
		if (m_playerRect.left == 144) {
			m_playerRect.left = 0;
		}
		else {
			m_playerRect.left += 48;
		}
		m_Sprite.setTextureRect(m_playerRect);
		clock.restart();
	}
}

FloatRect Player::getPosition() {
	return m_Sprite.getLocalBounds();
}

Sprite Player::getSprite() {
	return m_Sprite;
}