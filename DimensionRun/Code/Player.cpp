#include "Player.h"

Player::Player() {
	m_Health = INITIAL_HEALTH;
	m_Speed = INITIAL_SPEED;

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Free 3 Cyberpunk Sprites Pixel Art/2 Punk/Run/Punk_run.png"));
	m_Sprite.setTextureRect(IntRect{ 0, 0, 48, 48 });

	ani_counter = 1;
}

void Player::spawn(Vector2f resolution, float gravity) {
	// depending on resolution set position and scale of player
	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
		m_Sprite.setPosition(250, 1080);
		m_Sprite.setScale(6, 6);
	}
	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
		m_Sprite.setPosition(200, 850);
		m_Sprite.setScale(5, 5);
	}
	else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
		m_Sprite.setPosition(200, 800);
		m_Sprite.setScale(4.5, 4.5);
	}

	// store gravity for future use
	m_gravity = gravity;

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::update(float elapsedTime) {
	setSpriteFromSheet(IntRect(0, 0, 288, 48));
	moveTextureRect(elapsedTime);
}

void Player::setSpriteFromSheet(IntRect textureBox)
{
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	spriteSize = Vector2i(48, 48);

	if (textureBox.width > spriteSize.x)
	{
		animation_it_limit = textureBox.width / spriteSize.x;
	}
	else if (textureBox.height > spriteSize.y)
	{
		animation_it_limit = textureBox.height / spriteSize.y;
	}
	else
		throw logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");

	m_Sprite.setTextureRect(IntRect{ sheetCoordinate, spriteSize });

}

void Player::moveTextureRect(float elapsedTime) {
	if (ani_counter == animation_it_limit) {
		ani_counter = 0;
	}

	m_Sprite.setTextureRect(IntRect(sheetCoordinate + Vector2i(
		spriteSize.x * ani_counter, 0), spriteSize));

	// increment animation counter to point to next frame
	double timePerFrame;
	timePerFrame = 0.09;

	animationTimer += elapsedTime;
	if (animationTimer > timePerFrame) {
		ani_counter++;
		animationTimer = 0;
	}
}

FloatRect Player::getPosition() {
	return m_Sprite.getLocalBounds();
}

Sprite Player::getSprite() {
	return m_Sprite;
}