#include "EnemyCharacter.h"
#include "EntityManager.h"
#include "StateManager.h"

EnemyCharacter::EnemyCharacter(EntityManager* l_EntityMgr) :
	EntityBase(l_EntityMgr), m_SpriteSheet(m_EntityManager->GetContext()->m_TextureManager),
	m_JumpVelocity(250), m_HitPoints(1) {

	m_Name = "Character";
}

EnemyCharacter::~EnemyCharacter() { }

void EnemyCharacter::Move(const Direction& l_dir) {
	if (GetState() == EntityState::Dying) {
		return;
	}
}

void EnemyCharacter::Kill() {
	m_EntityManager->RemoveEntity(m_Id);
}

void EnemyCharacter::GetHurt(const int& l_Damage) {
	if (GetState() == EntityState::Dying) {
		return;
	}

	m_HitPoints = (m_HitPoints - l_Damage > 0 ? m_HitPoints - l_Damage : 0);

	SetState(EntityState::Dying);
}

int EnemyCharacter::GetHitpoints() {
	return m_HitPoints;
}

void EnemyCharacter::Load(const std::string& l_Path) {
	std::ifstream file;
	std::string line;

	file.open("Code/Resources/Media/Entities/" + l_Path);
	if (!file.is_open()) {
		std::cout << "! Failed loading file: " << l_Path << std::endl;
		return;
	}

	while (std::getline(file, line)) {
		if (line[0] == '|') {
			continue;
		}

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "Name") {
			keystream >> m_Name;
		}
		else if (type == "Spritesheet") {
			std::string path;
			keystream >> path;
			m_SpriteSheet.LoadSheet("Code/Resources/Media/Spritesheets/" + path);
		}
		else if (type == "Hitpoints") {
			keystream >> m_HitPoints;
		}
		else if (type == "BoundingBox") {
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;
			SetSize(boundingSize.x, boundingSize.y);
		}
		else if (type == "DamageBox") {
			keystream >> m_AttackAABBoffset.x >> m_AttackAABBoffset.y >>
				m_AttackAABB.width >> m_AttackAABB.height;
		}
		else if (type == "Speed") {
			keystream >> m_Speed.x >> m_Speed.y;
		}
		else if (type == "JumpVelocity") {
			keystream >> m_JumpVelocity;
		}
		else if (type == "MaxVelocity") {
			keystream >> m_MaxVelocity.x >> m_MaxVelocity.y;
		}
		else {
			std::cout << "! Unknown type in character file : " << type << std::endl;
		}
	}
	file.close();
}

void EnemyCharacter::UpdateAttackAABB() {
	m_AttackAABB.left = (m_AABB.left + m_AABB.width) + m_AttackAABBoffset.x;
	m_AttackAABB.top = m_AABB.top + m_AttackAABBoffset.y;
}

void EnemyCharacter::Animate() {
	EntityState state = GetState();

	if (state == EntityState::Idle && m_SpriteSheet.GetCurrentAnim()->GetName() != "Idle") {
		m_SpriteSheet.SetAnimation("Idle", true, true);
		//std::cout << "idle" << std::endl;
	}
	else if (state == EntityState::Dying && m_SpriteSheet.GetCurrentAnim()->GetName() != "Death") {
		m_SpriteSheet.SetAnimation("Death", true, false);
	}
}

void EnemyCharacter::Update(float l_deltaTime) {
	EntityBase::Update(l_deltaTime);

	if (m_AttackAABB.width != 0 && m_AttackAABB.height != 0) {
		UpdateAttackAABB();

		// Debug.
		if (m_EntityManager->GetContext()->m_DebugOverlay.Debug()) {
			sf::RectangleShape* arect = new sf::RectangleShape(sf::Vector2f(m_AttackAABB.width, m_AttackAABB.height));
			arect->setPosition(m_AttackAABB.left, m_AttackAABB.top);
			arect->setFillColor(sf::Color(255, 255, 255,
				(m_State == EntityState::Attacking && m_SpriteSheet.GetCurrentAnim()->IsInAction()
					? 200 : 100)));

			sf::RectangleShape* spriteSize = new sf::RectangleShape(sf::Vector2f(m_AABB.width, m_AABB.height));
			spriteSize->setPosition(m_AABB.left, m_AABB.top);
			spriteSize->setFillColor(sf::Color(0, 0, 0,
				(m_State == EntityState::Running && m_SpriteSheet.GetCurrentAnim()->IsInAction()
					? 200 : 100)));
			m_EntityManager->GetContext()->m_DebugOverlay.Add(arect);
			m_EntityManager->GetContext()->m_DebugOverlay.Add(spriteSize);
		}
		// End debug.
	}

	if (GetState() != EntityState::Dying){
		if (abs(m_Velocity.x) <= 0) {
			SetState(EntityState::Idle);
		}
	}
	else if (GetState() == EntityState::Dying) {
		//m_EntityManager->RemoveEntity(m_Id);
		if (!m_SpriteSheet.GetCurrentAnim()->IsPlaying()) {
			m_EntityManager->RemoveEntity(m_Id);
		}
	}

	Animate();
	m_SpriteSheet.Update(l_deltaTime);
	m_SpriteSheet.SetSpritePosition(m_Position);

	//std::cout << m_SpriteSheet.GetCurrentAnim()->GetName() << std::endl;
}

void EnemyCharacter::Draw(sf::RenderWindow* l_Window) {
	m_SpriteSheet.Draw(l_Window);
}