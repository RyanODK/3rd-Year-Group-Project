#ifndef MEDIUM_ENEMY_H
#define MEDIUM_ENEMY_H
#include "Enemy.h"

class MediumEnemy : public Enemy {
public:
	MediumEnemy(); // sets generic image for sprite as default

	void SetSprite(int enemyType); // brings in enemy sprite sheet and assigns a texture from the sheet to the sprite depending on what enemy type is needed
	void updateAnimation(int enemyType); // updates animation for sprite depending on enemy type using inherited functions from Enemy.h
};
#endif
