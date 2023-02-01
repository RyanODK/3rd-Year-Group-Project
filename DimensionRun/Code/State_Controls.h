#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Controls : public BaseState {
public:
	State_Controls(StateManager* l_StateManager);
	~State_Controls();

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
	sf::Text m_GameControlsTitle;
	sf::Text m_SoundTitle;
	sf::Text m_MusicTitle;
	sf::Text m_ArtistsTitle;

	sf::Text m_ProgrammerNames;
	sf::Text m_SoundNames;
	sf::Text m_MusicNames;
	sf::Text m_ArtistNames;

	sf::Text m_MainMenuText;

	std::string xboxAtextureString;
	sf::Sprite xboxA;

	sf::Texture* xboxATexture;
};