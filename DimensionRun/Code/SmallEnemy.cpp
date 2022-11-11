#include "SmallEnemy.h"

SmallEnemy::SmallEnemy() {
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Necromancer_creativekind-SheetIDLE.png", false));
	//m_Sprite.setTextureRect(IntRect{ 0, 0, 80, 80 });
}

void SmallEnemy::SetSprite(int enemyType)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Enemy/Small Enemy/EnemySpriteSheet.png", false));

	if (enemyType == 1) {
		// Demon
		m_Sprite.setTextureRect(IntRect{ 0, 0, 288, 212 });
	}
	else if (enemyType == 2) {
		// Nightborne
		m_Sprite.setTextureRect(IntRect{ 0, 848, 80, 80 });
	}
	else if (enemyType == 3) {
		// Necromancer
		m_Sprite.setTextureRect(IntRect{ 0, 1268, 159, 97 });
	}
}

void SmallEnemy::updateAnimation(int enemyType)
{
	if (enemyType == 1) {
		// Demon
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 165, 3456, 212 }, Vector2i(288, 212));
			moveTextureRect(0.09);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 0, 1728, 212 }, Vector2i(288, 212));
			moveTextureRect(0.18);
		}
	}
	else if (enemyType == 2) {
		// Nightborne
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 928, 480, 80 }, Vector2i(80, 80));
			moveTextureRect(0.09);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 848, 720, 80 }, Vector2i(80, 80));
			moveTextureRect(0.09);
		}
	}
	else if (enemyType == 3) {
		// Necromancer
		/*if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 1369, 1272, 97 }, Vector2i(159, 97));
			moveTextureRect(0.15);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 1268, 1272, 97 }, Vector2i(159, 97));
			moveTextureRect(0.15);
		}*/

		setSpriteFromSheet(IntRect{ 0, 1268, 1272, 97 }, Vector2i(159, 97));
		moveTextureRect(0.15);
	}
}
