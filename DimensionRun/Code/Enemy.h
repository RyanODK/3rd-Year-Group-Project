#pragma once
#include "EnemyCharacter.h"

class Enemy : public EnemyCharacter {
public:
	Enemy(EntityManager* l_entityMgr);
	~Enemy();

	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void Update(float l_dT);
private:
	sf::Vector2f m_Destination;
	bool m_HasDestination;
};