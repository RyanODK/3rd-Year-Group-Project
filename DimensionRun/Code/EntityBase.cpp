#include "EntityBase.h"

EntityBase::EntityBase(EntityManager* l_EntityMgr) :
	m_EntityManager(l_EntityMgr), m_Name("BaseEntity"),
	m_Type(EntityType::Base), m_ReferenceTile(nullptr),
	m_State(EntityState::Idle), m_Id(0),
	m_CollidingOnX(false), m_CollidingOnY(false) {}

void EntityBase::SetPosition(const float& l_X, const float& l_Y) {
	m_Position = sf::Vector2f(l_X, l_Y);
	UpdateAABB();
}

void EntityBase::SetPosition(const sf::Vector2f& l_Pos) {
	m_Position = l_Pos;
	UpdateAABB();
}

void EntityBase::SetSize(const float& l_X, const float& l_Y) {
	m_Size = sf::Vector2f(l_X, l_Y);
	UpdateAABB();
}

void EntityBase::SetState(const EntityState& l_State) {
	if (m_State == EntityState::Dying) {
		return;
	}
	m_State = l_State;
}

void EntityBase::Move(float l_X, float l_Y) {
	m_PositionOld = m_Position;
	m_Position += sf::Vector2f(l_X, l_Y);

	sf::Vector2u mapSize = m_EntityManager->GetContext()->m_GameMap->GetMapSize();

	if (m_Position.x < 0) {
		m_Position.x = 0;
	}
	else if (m_Position.x > (mapSize.x + 1) * Sheet::Tile_Size) {
		m_Position.x = (mapSize.x + 1) * Sheet::Tile_Size;
	}

	if (m_Position.y < 0) {
		m_Position.y = 0;
	}
	else if (m_Position.y > (mapSize.y + 1) * Sheet::Tile_Size) {
		m_Position.y = (mapSize.y + 1) * Sheet::Tile_Size;
		SetState(EntityState::Dying);
	}

	UpdateAABB();
}

void EntityBase::AddVelocity(float l_X, float l_Y) {
	m_Velocity += sf::Vector2f(l_X, l_Y);

	if (abs(m_Velocity.x) > m_MaxVelocity.x) {
		if (m_Velocity.x < 0) {
			m_Velocity.x = -m_MaxVelocity.x;
		}
		else {
			m_Velocity.x = m_MaxVelocity.x;
		}

		if (abs(m_Velocity.y) > m_MaxVelocity.y) {
			if (m_Velocity.y < 0) {
				m_Velocity.y = -m_MaxVelocity.y;
			}
			else {
				m_Velocity.y = m_MaxVelocity.y;
			}
		}
	}
}

void EntityBase::Accelerate(float l_X, float l_Y) {
	m_Acceleration += sf::Vector2f(l_X, l_Y);
}

void EntityBase::ApplyFriction(float l_X, float l_Y) {
	if (m_Velocity.x != 0) {
		if (abs(m_Velocity.x) - abs(l_X) < 0) {
			m_Velocity.x = 0;
		}
		else {
			m_Velocity.x -= l_X;
		}
	}

	if (m_Velocity.y != 0) {
		if (abs(m_Velocity.y) - abs(l_Y) < 0) {
			m_Velocity.y = 0;
		}
		else {
			if (m_Velocity.y < 0) {
				m_Velocity.y += l_Y;
			}
			else {
				m_Velocity.y -= l_Y;
			}
		}
	}
}

std::string EntityBase::GetName() {
	return m_Name;
}

unsigned int EntityBase::GetId() {
	return m_Id;
}

EntityType EntityBase::GetType() {
	return m_Type;
}

EntityState EntityBase::GetState() {
	return m_State;
}

bool EntityBase::SortCollisions(const CollisionElement& l_One, const CollisionElement& l_Two) {
	return l_One.m_Area > l_Two.m_Area;
}

void EntityBase::CheckCollisions() {
	Map* gameMap = m_EntityManager->GetContext()->m_GameMap;
	unsigned int tileSize = gameMap->GetTileSize();

	int fromX = floor(m_AABB.left / tileSize);
	int fromY = floor(m_AABB.top / tileSize);
	int toX = floor((m_AABB.left + m_AABB.width) / tileSize);
	int toY = floor((m_AABB.top + m_AABB.height) / tileSize);

	for (int x = fromX; x <= toX; x++) {
		for (int y = fromY; y <= toY; y++) {
			Tile* tile = gameMap->GetTile(x, y);

			if (!tile) {
				continue;
			}

			sf::FloatRect tileBounds(x * tileSize, y * tileSize, tileSize, tileSize);
			sf::FloatRect intersection;

			m_AABB.intersects(tileBounds, intersection);

			float area = intersection.width * intersection.height;

			CollisionElement e(area, tile->m_Properties, tileBounds);
			m_Collisions.emplace_back(e);

			if (tile->m_Warp && m_Type == EntityType::Player) {
				gameMap->LoadNext();
			}
		}
	}
}

void EntityBase::ResolveCollisions() {
	if (!m_Collisions.empty()) {
		std::sort(m_Collisions.begin(), m_Collisions.end(), SortCollisions);

		Map* gameMap = m_EntityManager->GetContext()->m_GameMap;
		unsigned int tileSize = gameMap->GetTileSize();

		for (auto& itr : m_Collisions) {
			if (!m_AABB.intersects(itr.m_TileBounds)) {
				continue;
			}

			float xDiff = (m_AABB.left + (m_AABB.width / 2)) -
				(itr.m_TileBounds.left + (itr.m_TileBounds.width / 2));
			float yDiff = (m_AABB.top + (m_AABB.height / 2)) -
				(itr.m_TileBounds.top + (itr.m_TileBounds.height / 2));
			float resolve = 0;

			if (abs(xDiff) > abs(yDiff)) {
				if (xDiff > 0) {
					resolve = (itr.m_TileBounds.left + tileSize) -
						m_AABB.left;
				}
				else {
					resolve = -((m_AABB.left + m_AABB.width) -
						itr.m_TileBounds.left);
				}
				Move(resolve, 0);
				m_Velocity.x = 0;
				m_CollidingOnX = true;
			}
			else {
				if (yDiff > 0) {
					resolve = (itr.m_TileBounds.top + tileSize) -
						m_AABB.top;
				}
				else {
					resolve = -((m_AABB.top + m_AABB.height) - 
						itr.m_TileBounds.top);
				}
				Move(0, resolve);
				m_Velocity.y = 0;

				if (m_CollidingOnY) { 
					continue; 
				}

				m_ReferenceTile = itr.m_Tile;
				m_CollidingOnY = true;
			}
		}
		m_Collisions.clear();
	}

	if (!m_CollidingOnY) { 
		m_ReferenceTile = nullptr; 
	}
}

void EntityBase::Update(float l_DeltaTime) {
	Map* map = m_EntityManager->GetContext()->m_GameMap;
	float gravity = map->GetGravity();

	Accelerate(0, gravity);
	AddVelocity(m_Acceleration.x * l_DeltaTime, m_Acceleration.y * l_DeltaTime);
	SetAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue;

	if (m_ReferenceTile) {
		frictionValue = m_ReferenceTile->m_Friction;

		if (m_ReferenceTile->m_Deadly) {
			SetState(EntityState::Dying);
		}
	}
	else if (map->GetDefaultTile()) {
		frictionValue = map->GetDefaultTile()->m_Friction;
	}
	else {
		frictionValue = m_Friction;
	}

	float frictionX = (m_Speed.x * frictionValue.x) * l_DeltaTime;
	float frictionY = (m_Speed.y * frictionValue.y) * l_DeltaTime;

	ApplyFriction(frictionX, frictionY);

	sf::Vector2f deltaPos = m_Velocity * l_DeltaTime;
	Move(deltaPos.x, deltaPos.y);

	m_CollidingOnX = false;
	m_CollidingOnY = false;

	CheckCollisions();
	ResolveCollisions();
}

void EntityBase::UpdateAABB() {
	m_AABB = sf::FloatRect(m_Position.x - (m_Size.x / 2), m_Position.y - m_Size.y, m_Size.x, m_Size.y);
}