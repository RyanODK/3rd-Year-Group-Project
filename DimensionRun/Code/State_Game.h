#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "Background.h"
#include "TextureHolder.h"
#include "Player.h"
#include "SmallEnemy.h"
#include "FloatingObstacle.h"
#include "GroundObstacle.h"
#include "SoundManager.h"

class State_Game : public BaseState {
public:
	State_Game(StateManager* l_StateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void Jump(EventDetails* l_Details);

	Player* GetPlayer() {
		return &m_player;
	};

	Background* GetBackground() {
		return &m_background;
	};

	SmallEnemy* GetSmallEnemy1() {
		return &m_SmallEnemy1;
	}

	SmallEnemy* GetSmallEnemy2() {
		return &m_SmallEnemy2;
	}

	SmallEnemy* GetSmallEnemy3() {
		return &m_SmallEnemy3;
	}

	SmallEnemy* GetSmallEnemy4() {
		return &m_SmallEnemy4;
	}

	SmallEnemy* GetSmallEnemy5() {
		return &m_SmallEnemy5;
	}

	FloatingObstacle* GetFloatingObstacle() {
		return &m_FloatingObstacle;
	}

	GroundObstacle* GetGroundObstacle() {
		return &m_GroundObstacle;
	}

	SoundManager* GetSoundManager() {
		return &m_SoundManager;
	}

	void MainMenu(EventDetails* l_Details);
	void Pause(EventDetails* l_Details);

private:
	TextureHolder m_TextureHolder;
	sf::Vector2f m_Resolution;

	sf::Font m_Font;
	sf::Text distanceText; 
	sf::Text bestDistanceText;
	sf::Text coinCountText;

	Background m_background;
	Player m_player;

	float resetTime;
	float distanceRan = 0.0f; // track distance
	float bestDistance = 0.0f; // keeps best time
	float coinCount = 0.0f; // coin counter

	int backgroundType;
	int groundHeight;
	const float gravity = 450;

	/* Small Enemies */
	SmallEnemy m_SmallEnemy1;
	SmallEnemy m_SmallEnemy2;
	SmallEnemy m_SmallEnemy3;
	SmallEnemy m_SmallEnemy4;
	SmallEnemy m_SmallEnemy5;
	//SmallEnemy m_Portal;

	/* Obstacles */
	FloatingObstacle m_FloatingObstacle;
	GroundObstacle m_GroundObstacle;

	SoundManager m_SoundManager;
};
