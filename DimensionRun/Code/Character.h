#pragma once
#include "EntityBase.h"
#include "SpriteSheet.h"

class Character : public EntityBase {
	friend class EntityManager;

public:
	Character(EntityManager* l_EntityMgr);
	virtual ~Character();

	void Move(const Direction& l_dir);
	void Jump();
	void Attack();
	void GetHurt(const int& l_Damage);
	void Load(const std::string& l_Path);
	void Draw(sf::RenderWindow* l_Window);

	virtual void OnEntityCollision(EntityBase* l_Collider, bool l_Attack) = 0;
	virtual void Update(float l_DeltaTime);

protected:
	void UpdateAttackAABB();
	void Animate();
	SpriteSheet m_SpriteSheet;
	float m_JumpVelocity;
	int m_HitPoints;
	sf::FloatRect m_AttackAABB;
	sf::Vector2f m_AttackAABBoffset;
};
