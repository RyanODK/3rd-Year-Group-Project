#include "Player.h"
#include "EntityManager.h"
#include "StateManager.h" 

Player::Player(EntityManager* l_EntityMgr) :
	Character(l_EntityMgr) {

	Load("Player.char");
	m_Type = EntityType::Player;

	EventManager* events = m_EntityManager->GetContext()->m_EventManager;
	events->AddCallback<Player>(StateType::Game, "Player_JumpKeyboard", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_JumpJoystick", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Attack", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_SlideKeyboard", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_SlideJoystick", &Player::React, this);
}
 
Player::~Player() {
	EventManager* events = m_EntityManager->GetContext()->m_EventManager;
	events->RemoveCallback(StateType::Game, "Player_JumpKeyboard");
	events->RemoveCallback(StateType::Game, "Player_JumpJoystick");
	events->RemoveCallback(StateType::Game, "Player_Attack");
	events->RemoveCallback(StateType::Game, "Player_SlideKeyboard");
	events->RemoveCallback(StateType::Game, "Player_SlideJoystick");
}

void Player::OnEntityCollision(EntityBase* l_Collider, bool l_Attack) {
	if (m_State == EntityState::Dying) {
		deathSound.play();
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

		
		EnemyCharacter* opponent = (EnemyCharacter*)l_Collider;
		opponent->GetHurt(1);

		/*if (m_Position.x > opponent->GetPosition().x) {
			opponent->AddVelocity(-32, 0);
		}
		else {
			opponent->AddVelocity(32, 0);
		}*/
	}
	else {
		EnemyCharacter* opponent = (EnemyCharacter*)l_Collider;
		if (opponent->GetName() == "Coin") {
			coinSound.play();
			opponent->Kill();
			coinCount++;
			//std::cout << coinCount << std::endl;
		}
	}
}

void Player::React(EventDetails* l_Details) {
	if (l_Details->m_Name == "Player_JumpKeyboard" || l_Details->m_Name == "Player_JumpJoystick") {
		Character::Jump();

		if (abs(m_Velocity.y) == 300) {
			jumpSound.play();
		}
	}
	else if (l_Details->m_Name == "Player_Attack") {
		Character::Attack();
	}
	else if (l_Details->m_Name == "Player_SlideKeyboard" || l_Details->m_Name == "Player_SlideJoystick") {
		Character::Slide();
	}
}