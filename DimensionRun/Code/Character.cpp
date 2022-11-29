#include "Character.h"

Character::Character(EntityManager* l_EntityMgr) :
	EntityBase(l_EntityMgr), m_SpriteSheet(m_EntityManager->GetContext()->m_TextureManager),
	m_JumpVelocity(250), m_HitPoints(1) {

	m_Name = "Character";
}

void Character::Move() {
	if (GetState() == EntityState::Dying) {
		return;
	}

	Accelerate(m_Speed.x, 0);

	if (GetState() == EntityState::Idle) {
		SetState(EntityState::Running);
	}
}

void Character::Jump() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping) {
		return;
	}

	SetState(EntityState::Jumping);
	AddVelocity(0, -m_JumpVelocity);
}

void Character::Attack() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping || GetState() == EntityState::Attacking) {
		return;
	}
	SetState(EntityState::Attacking);
}

void Character::GetHurt(const int& l_Damage) {
	if (GetState() == EntityState::Dying) {
		return;
	}

	m_HitPoints = (m_HitPoints - l_Damage > 0 ? m_HitPoints - l_Damage : 0);

	/*if (m_HitPoints) {
		SetState(EntityState::Dying);
	}
	else {
		SetState
	}*/

	SetState(EntityState::Dying);
}

void Character::Load(const std::string& l_Path) {
	std::ifstream file;
	std::string line;

	file.open(Utils::GetWorkingDirectory() + std::string("Code/") + l_Path);
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
		else if (type == "SpriteSheet") {
			std::string path;
			keystream >> path;
			m_SpriteSheet.LoadSheet("Code/" + path);
		}
		else if (type == "HitPoints") {
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

void Character::UpdateAttackAABB() {
	m_AttackAABB.left = (m_AABB.left + m_AABB.width) + m_AttackAABBoffset.x;
	m_AttackAABB.top = m_AABB.top + m_AttackAABBoffset.y;
}

void Character::Animate() {
	EntityState state = GetState();

	if (state == EntityState::Running && m_SpriteSheet.GetCurrentAnim()->GetName() != "Run") {
		m_SpriteSheet.SetAnimation("Run", true, true);
	}
	else if (state == EntityState::Jumping && m_SpriteSheet.GetCurrentAnim()->GetName() != "Jump") {
		m_SpriteSheet.SetAnimation("Jump", true, false);
	}
	else if (state == EntityState::Attacking && m_SpriteSheet.GetCurrentAnim()->GetName() != "Attack") {
		m_SpriteSheet.SetAnimation("Attack", true, false);
	}
	else if (state == EntityState::Dying && m_SpriteSheet.GetCurrentAnim()->GetName() != "Death") {
		m_SpriteSheet.SetAnimation("Death", true, false);
	}
}

void Character::Update(float l_deltaTime) {
	EntityBase::Update(l_deltaTime);

	if (m_AttackAABB.width != 0 && m_AttackAABB.height != 0) {
		UpdateAttackAABB();
	}

	if (GetState() != EntityState::Dying && GetState() != EntityState::Attacking) {
		if (abs(m_Velocity.y) >= 0.001f) {
			SetState(EntityState::Jumping);
		}
		else if (abs(m_Velocity.x) >= 0.1f) {
			SetState(EntityState::Running);
		}
		/*else {
			SetState(EntityState::)
		}*/
	}
	else if (GetState() == EntityState::Attacking) {
		if (!m_SpriteSheet.GetCurrentAnim()->IsPlaying()) {
			SetState(EntityState::Running);
		}
	}
	else if (GetState() == EntityState::Dying) {
		if (!m_SpriteSheet.GetCurrentAnim()->IsPlaying()) {
			m_EntityManager->Remove(m_Id);
		}
	}
	Animate();
	m_SpriteSheet.Update(l_deltaTime);
	m_SpriteSheet.SetSpritePosition(m_Position);
}

void Character::Draw(sf::RenderWindow* l_Window) {
	m_SpriteSheet.Draw(l_Window);
}