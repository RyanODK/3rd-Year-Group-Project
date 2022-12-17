#pragma once
#include "Character.h"
#include "EventManager.h"

class Player : public Character {
public:
	Player(EntityManager* l_EntityMgr);
	~Player();

	void OnEntityCollision(EntityBase* l_Collider, bool l_Attack);
	void React(EventDetails* l_Details);
};
