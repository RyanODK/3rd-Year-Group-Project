#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Background.h"
#include "TextureHolder.h"
#include "EventManager.h"

class State_GameOver : public BaseState {
public:
	State_GameOver(StateManager* l_StateManager);
	~State_GameOver();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void MainMenu(EventDetails* l_Details); // switches state to MainMenu state
	void Pause(EventDetails* l_Details); // switches state to Pause state

	void ToggleOverlay(EventDetails* l_details);

private:
	sf::Font m_Font;
	sf::Text coinCountText;
	Map* m_GameMap;
	int coinCount;
};
