#include "Enemy.h"

Enemy::Enemy(EntityManager * l_entityMgr)
	:EnemyCharacter(l_entityMgr), m_HasDestination(false) {
	m_Type = EntityType::Enemy;
}

Enemy::~Enemy() {}

void Enemy::OnEntityCollision(EntityBase* l_collider, bool l_attack)
{
	//if (m_State == EntityState::Dying) { return; }
	//if (l_attack) { return; }
	//if (l_collider->GetType() != EntityType::Player) { return; }
	//EnemyCharacter* player = (EnemyCharacter*)l_collider;
	//SetState(EntityState::Attacking);
	//player->GetHurt(1);
	///*if (m_Position.x > player->GetPosition().x) {
	//	player->AddVelocity(-m_Speed.x, 0);
	//}
	//else {
	//	player->AddVelocity(m_Speed.y, 0);
	//}*/
}

void Enemy::Update(float l_dT) {
	EnemyCharacter::Update(l_dT);

	/*if (m_HasDestination) {
		if (abs(m_Destination.x - m_Position.x) < 16) { m_HasDestination = false; return; }
		if (m_Destination.x - m_Position.x > 0) { Move(Direction::Right); }
		else { Move(Direction::Left); }
		if (m_CollidingOnX) { m_HasDestination = false; }
		return;
	}
	int random = rand() % 1000 + 1;
	if (random != 1000) { return; }
	int newX = rand() % 65 + 0;
	if (rand() % 2) { newX = -newX; }
	m_Destination.x = m_Position.x + newX;
	if (m_Destination.x < 0) { m_Destination.x = 0; }
	m_HasDestination = true;*/
}

