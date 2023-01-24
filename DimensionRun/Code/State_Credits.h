#pragma once
#include "BaseState.h"
#include "Map.h"
#include "Background.h"
#include "TextureHolder.h"
#include "EventManager.h"

class State_Credits : public BaseState {
public:
	State_Credits(StateManager* l_StateManager);
	~State_Credits();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void MainMenu(EventDetails* l_Details); // switches state to MainMenu state

private:
	sf::Font m_Font;

	sf::Text m_MainTitle;
	sf::Text m_ProgrammerTitle;
	sf::Text m_SoundTitle;
	sf::Text m_MusicTitle;
	sf::Text m_ArtistsTitle;

	sf::Text m_ProgrammerNames;
	sf::Text m_SoundNames;
	sf::Text m_MusicNames;
	sf::Text m_ArtistNames;

	sf::Text m_MainMenuText;
};
