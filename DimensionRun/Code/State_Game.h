#pragma once
#include "BaseState.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

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

	void MainMenu(EventDetails* l_Details); // switches state to MainMenu state
	void Pause(EventDetails* l_Details); // switches state to Pause state

	void PlayerMove(EventDetails* l_Details);
	void ToggleOverlay(EventDetails* l_details);

private:
	void UpdateCamera();

	Map* m_GameMap;
	int m_Player;
};
