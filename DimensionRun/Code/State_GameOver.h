#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BaseState.h"
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

	void Retry(EventDetails* l_Details);
	void MainMenu(EventDetails* l_Details); // switches state to MainMenu state

private:
	sf::SoundBuffer buttonBuffer;
	sf::Sound buttonSound;
};
