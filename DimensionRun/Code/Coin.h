#pragma once
#include "CoinEntity.h"

class Coin : public CoinEntity {
public:
	Coin(EntityManager* l_entityMgr);
	~Coin();

	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void Update(float l_dT);
private:
	sf::Vector2f m_Destination;
	bool m_HasDestination;
};