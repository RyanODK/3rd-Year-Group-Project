#include "LargeEnemy.h"

LargeEnemy::LargeEnemy() {
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"Graphics/Necromancer_creativekind-SheetIDLE.png", false));
	//m_Sprite.setTextureRect(IntRect{ 0, 0, 80, 80 });
}

void LargeEnemy::SetSprite(int enemyType)
{
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"Graphics/Enemy/Small Enemy/EnemySpriteSheet.png", false));

	if (enemyType == 1) {
		// Demon
		m_Sprite.setTextureRect(sf::IntRect{ 0, 0, 288, 212 });
	}
	else if (enemyType == 2) {
		// Nightborne
		m_Sprite.setTextureRect(sf::IntRect{ 0, 848, 80, 80 });
	}
	else if (enemyType == 3) {
		// Necromancer
		m_Sprite.setTextureRect(sf::IntRect{ 0, 1268, 159, 97 });
	}
}

void LargeEnemy::updateAnimation(int enemyType)
{
	if (enemyType == 1) {
		// Demon
		setSpriteFromSheet(sf::IntRect{ 0, 0, 1728, 212 }, sf::Vector2i(288, 212));
		moveTextureRect(0.18);
	}
	else if (enemyType == 2) {
		// Nightborne
		setSpriteFromSheet(sf::IntRect{ 0, 848, 720, 80 }, sf::Vector2i(80, 80));
		moveTextureRect(0.09);
	}
	else if (enemyType == 3) {
		// Necromancer
		setSpriteFromSheet(sf::IntRect{ 0, 1268, 1272, 97 }, sf::Vector2i(159, 97));
		moveTextureRect(0.15);
	}
}
