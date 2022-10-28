#include "Enemy.h"
#include "TextureHolder.h"

void Enemy::spawn(Vector2f startPosition, Vector2f scale) {
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	m_Sprite.setScale(scale);

	m_Sprite.setPosition(m_Position);
}

void Enemy::update(float elapsedTime) {
	timeElapsed = elapsedTime;
}

void Enemy::setSpriteFromSheet(IntRect textureBox, Vector2i size)
{
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	spriteSize = size;

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

void Enemy::moveTextureRect(double frameTime) {
	if (ani_counter == animation_it_limit) {
		ani_counter = 0;
	}

	m_Sprite.setTextureRect(IntRect(sheetCoordinate + Vector2i(
		spriteSize.x * ani_counter, 0), spriteSize));

	// increment animation counter to point to next frame
	double timePerFrame;
	timePerFrame = frameTime;

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