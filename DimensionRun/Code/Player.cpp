#include "Player.h"
#include "EntityManager.h"
#include "StateManager.h" 

Player::Player(EntityManager* l_EntityMgr) :
	Character(l_EntityMgr) {

	Load("Player.char");
	m_Type = EntityType::Player;

	EventManager* events = m_EntityManager->GetContext()->m_EventManager;
	events->AddCallback<Player>(StateType::Game, "Player_MoveLeft", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_MoveRight", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Jump", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Attack", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Slide", &Player::React, this);
}
 
Player::~Player() {
	EventManager* events = m_EntityManager->GetContext()->m_EventManager;
	events->RemoveCallback(StateType::Game, "Player_MoveLeft");
	events->RemoveCallback(StateType::Game, "Player_MoveRight");
	events->RemoveCallback(StateType::Game, "Player_Jump");
	events->RemoveCallback(StateType::Game, "Player_Attack");
	events->RemoveCallback(StateType::Game, "Player_Slide");
}

void Player::OnEntityCollision(EntityBase* l_Collider, bool l_Attack) {
	if (m_State == EntityState::Dying) {
		return;
	}

	if (l_Attack) {
		if (m_State != EntityState::Attacking) {
			return;
		}

		if (!m_SpriteSheet.GetCurrentAnim()->IsInAction()) {
			return;
		}

		if (l_Collider->GetType() != EntityType::Enemy &&
			l_Collider->GetType() != EntityType::Player) {
			return;
		}

		
		Character* opponent = (Character*)l_Collider;
		opponent->GetHurt(1);

		/*if (m_Position.x > opponent->GetPosition().x) {
			opponent->AddVelocity(-32, 0);
		}
		else {
			opponent->AddVelocity(32, 0);
		}*/
	}
	else {
		Character* opponent = (Character*)l_Collider;
		if (opponent->GetName() == "Cyborg") {
			std::cout << "colliding with enemy character: " << l_Collider->GetName() << std::endl;
		}
		// other behaviour
	}
}

void Player::React(EventDetails* l_Details) {
	if (l_Details->m_Name == "Player_MoveLeft") {
		Character::Move(Direction::Left);
	}
	else if (l_Details->m_Name == "Player_MoveRight") {
		Character::Move(Direction::Right);
	}
	else if (l_Details->m_Name == "Player_Jump") {
		Character::Jump();
	}
	else if (l_Details->m_Name == "Player_Attack") {
		Character::Attack();
	}
	else if (l_Details->m_Name == "Player_Slide") {
		Character::Slide();
	}
}