#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Background.h"
#include "TextureHolder.h"
#include "EventManager.h"

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

	void ToggleOverlay(EventDetails* l_details);

private:
	Map* m_GameMap;
};
