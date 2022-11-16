#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "Background.h"
#include "TextureHolder.h"
#include "Player.h"
#include "SmallEnemy.h"

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

	Player* GetPlayer() {
		return &m_player;
	};

	Background* GetBackground() {
		return &m_background;
	};

private:
	TextureHolder m_TextureHolder;

	sf::Font m_Font;

	Background m_background;
	Player m_player;

	float resetTime;
};
