#include "Enemy.h"
#include "TextureHolder.h"

Enemy::Enemy() {
	m_Health = INITIAL_HEALTH;
	m_Speed = INITIAL_SPEED;

	/*m_Sprite.setTexture(m_Texture);
	m_Sprite.setTextureRect(m_EnemyRect);*/

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Necromancer_creativekind-Sheet.png"));
	m_Sprite.setTextureRect(IntRect{ 0, 149, 158, 128 });

	ani_counter = 1;
}

void Enemy::spawn(Vector2f resolution, float elapsedTime) {
	// depending on resolution set position and scale of player
	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
		m_Sprite.setPosition(500, 700);
		m_Sprite.setScale(6, 6);
	}
	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
		m_Sprite.setPosition(200, 850);
		m_Sprite.setScale(4, 4);
	}
	else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
		m_Sprite.setPosition(500, 800);
		m_Sprite.setScale(2, 2);
	}

	timeElapsed = elapsedTime;

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Enemy::update() {
	setSpriteFromSheet(IntRect(0, 149, 1264, 128));
	moveTextureRect();
}

void Enemy::setSpriteFromSheet(IntRect textureBox)
{
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	spriteSize = Vector2i(158, 128);

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

void Enemy::moveTextureRect() {
	if (ani_counter == animation_it_limit) {
		ani_counter = 0;
	}

	m_Sprite.setTextureRect(IntRect(sheetCoordinate + Vector2i(
		spriteSize.x * ani_counter, 0), spriteSize));

	// increment animation counter to point to next frame
	double timePerFrame;
	timePerFrame = 75;

	animationTimer += timeElapsed;
	if (animationTimer > timePerFrame) {
		ani_counter++;
		animationTimer = 0;
	}
}

FloatRect Enemy::getPosition() {
	return m_Sprite.getLocalBounds();
}

Sprite Enemy::getSprite() {
	return m_Sprite;
}