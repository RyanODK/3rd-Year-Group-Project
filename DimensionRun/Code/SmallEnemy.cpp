#include "SmallEnemy.h"

SmallEnemy::SmallEnemy() {
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Necromancer_creativekind-SheetIDLE.png", false));
	//m_Sprite.setTextureRect(IntRect{ 0, 0, 80, 80 });
}

void SmallEnemy::SetSprite(int enemyType)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Enemy/Small Enemy/smallEnemySpritesheet.png", false));

	if (enemyType == 1) {
		// Cyborg
		m_Sprite.setTextureRect(IntRect{ 0, 0, 32, 32 });
	}
	else if (enemyType == 2) {
		// turret
		m_Sprite.setTextureRect(IntRect{ 0, 100, 25, 22 });
	}
	else if (enemyType == 3) {
		// old man
		m_Sprite.setTextureRect(IntRect{ 0, 123, 23, 32 });
	}
	else if (enemyType == 4) {
		// ghost
		m_Sprite.setTextureRect(IntRect{ 0, 220, 34, 54 });
	}
	else if (enemyType == 5) {
		// huntress
		m_Sprite.setTextureRect(IntRect{ 0, 351, 50, 34 });
	}
	else if(enemyType == 6) {
		// portal
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"Graphics/purplePortalEffect.png", false));
		m_Sprite.setTextureRect(IntRect{ 0, 0, 600, 475 });
	}
}

void SmallEnemy::updateAnimation(int enemyType)
{
	if (enemyType == 1) {
		// Cyborg
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 67, 192, 31 }, Vector2i(32, 32));
			moveTextureRect(0.09);
		}

		if (EnemyAttack) {
			setSpriteFromSheet(IntRect{ 0, 0, 216, 32 }, Vector2i(36, 32));
			moveTextureRect(0.17);
		}
	}
	else if (enemyType == 2) {
		// turret
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 100, 150, 22 }, Vector2i(25, 22));
			moveTextureRect(0.2);
		}
		/*else {
			setSpriteFromSheet(IntRect{ 0, 100, 66, 54 }, Vector2i(33, 54));
			moveTextureRect(0.09);
		}*/
	}
	else if (enemyType == 3) {
		// old man
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 186, 132, 32 }, Vector2i(22, 34));
			moveTextureRect(0.09);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 123, 92, 32 }, Vector2i(23, 32));
			moveTextureRect(0.15);
		}
	}
	else if (enemyType == 4) {
		// ghost
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 220, 136, 32 }, Vector2i(34, 54));
			moveTextureRect(0.15);
		}
	}
	else if (enemyType == 5) {
		// huntress
		if (EnemyActive) {
			setSpriteFromSheet(IntRect{ 0, 351, 400, 34 }, Vector2i(50, 34));
			moveTextureRect(0.12);
		}
		else {
			setSpriteFromSheet(IntRect{ 0, 274, 336, 34 }, Vector2i(48, 42));
			moveTextureRect(0.15);
		}
	}
	else if (enemyType == 6) {
		// portal
		/*m_Sprite = Sprite(TextureHolder::GetTexture(
			"Graphics/portalEffect.png", false));*/
		setSpriteFromSheet(IntRect{ 0, 0, 9600, 475 }, Vector2i(480, 475));
		moveTextureRect(0.05);
		
	}
}
