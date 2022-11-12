#include "MediumEnemy.h"

MediumEnemy::MediumEnemy() {
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Necromancer_creativekind-SheetIDLE.png", false));
	//m_Sprite.setTextureRect(IntRect{ 0, 0, 80, 80 });
}

void MediumEnemy::SetSprite(int enemyType)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Enemy/Small Enemy/smallEnemySpritesheet.png", false));

	if (enemyType == 1) {
		// Cyborg
		m_Sprite.setTextureRect(IntRect{ 0, 0, 32, 32 });
	}
	else if (enemyType == 2) {
		// egg turret
		m_Sprite.setTextureRect(IntRect{ 0, 100, 33, 59 });
	}
	else if (enemyType == 3) {
		// old man
		m_Sprite.setTextureRect(IntRect{ 0, 278, 23, 32 });
	}
}

void MediumEnemy::updateAnimation(int enemyType)
{
	if (enemyType == 1) {
		// Cyborg
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 67, 192, 31 }, Vector2i(32, 32));
			moveTextureRect(0.09);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 0, 216, 32 }, Vector2i(36, 32));
			moveTextureRect(0.17);
		}
	}
	else if (enemyType == 2) {
		// Egg Turret
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 154, 131, 59 }, Vector2i(33, 59));
			moveTextureRect(0.2);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 100, 66, 54 }, Vector2i(33, 54));
			moveTextureRect(0.09);
		}
	}
	else if (enemyType == 3) {
		// old man
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 277, 132, 32 }, Vector2i(22, 34));
			moveTextureRect(0.09);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 213, 92, 32 }, Vector2i(23, 32));
			moveTextureRect(0.15);
		}
	}
}