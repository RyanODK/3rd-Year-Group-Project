#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
//#include "EntityManager.h"
//#include "SharedContext.h"
//#include "Map.h"

enum class EntityType { Base, Enemy, Player };

enum class EntityState {
	Running, Jumping, Attacking, Dying
};

struct TileInfo;

struct CollisionElement {
	CollisionElement(float l_Area, TileInfo* l_Info, const sf::FloatRect& l_Bounds) :
		m_Area(l_Area), m_Tile(l_Info),
		m_TileBounds(l_Bounds) {}

	float m_Area;
	TileInfo* m_Tile;
	sf::FloatRect m_TileBounds;
};

using Collisions = std::vector<CollisionElement>;
bool SortCollisions(const CollisionElement& l_One, const CollisionElement& l_Two);

class EntityManager;

class EntityBase {
	friend class EntityManager;

public:
	EntityBase(EntityManager* l_EntityMgr);
	virtual ~EntityBase();

	void Move(float l_X, float l_Y);
	void AddVelocity(float l_X, float l_Y);
	void Accelerate(float l_X, float l_Y);
	void ApplyFriction(float l_X, float l_Y);

	void SetAcceleration(float l_X, float l_Y);
	void SetPosition(const float& l_X, const float& l_Y);
	void SetPosition(const sf::Vector2f& l_Pos);
	void SetSize(const float& l_X, const float& l_Y);
	void SetState(const EntityState& l_State);

	std::string GetName();
	unsigned int GetId();
	EntityType GetType();
	EntityState GetState();
	const sf::Vector2f& GetPosition() const;
	//bool SortCollisions(const CollisionElement& l_One, const CollisionElement& l_Two);

	virtual void Update(float l_deltaTime);
	virtual void Draw(sf::RenderWindow* l_Wind) = 0;

protected:
	// Methods.
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();
	// Method for what THIS entity does TO the l_collider entity.
	virtual void OnEntityCollision(EntityBase* l_Collider, bool l_Attack) = 0;

	// Data members.
	std::string m_Name;
	EntityType m_Type;
	unsigned int m_Id; // Entity id in the entity manager.
	sf::Vector2f m_Position; // Current position.
	sf::Vector2f m_PositionOld; // Position before entity moved.
	sf::Vector2f m_Velocity; // Current velocity.
	sf::Vector2f m_MaxVelocity; // Maximum velocity.
	sf::Vector2f m_Speed; // Value of acceleration.
	sf::Vector2f m_Acceleration; // Current acceleration.
	sf::Vector2f m_Friction; // Default friction value.
	TileInfo* m_ReferenceTile; // Tile underneath entity.
	sf::Vector2f m_Size; // Size of the collision box.
	sf::FloatRect m_AABB; // The bounding box for collisions.
	EntityState m_State; // Current entity state.
	// Flags for remembering axis collisions.
	bool m_CollidingOnX;
	bool m_CollidingOnY;

	Collisions m_Collisions;
	EntityManager* m_EntityManager;
};
