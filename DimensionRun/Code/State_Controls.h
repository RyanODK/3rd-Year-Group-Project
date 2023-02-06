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
	sf::Text m_MainMenuControlsTitle;
	sf::Text m_MusicTitle;
	sf::Text m_ArtistsTitle;

	sf::Text m_InGameControls;
	sf::Text m_MainMenuControls;
	sf::Text m_MusicNames;
	sf::Text m_ArtistNames;

	sf::Text m_MainMenuText;

	std::string xboxAtextureString;
	std::string xboxBtextureString;
	std::string xboxXtextureString;
	std::string xboxYtextureString;
	std::string xboxMenutextureString;
	std::string xboxWindowtextureString;

	sf::Sprite xboxA;
	sf::Sprite xboxA1;
	sf::Sprite xboxB;
	sf::Sprite xboxB1;
	sf::Sprite xboxX;
	sf::Sprite xboxY;
	sf::Sprite xboxY1;
	sf::Sprite xboxMenu;
	sf::Sprite xboxWindow;

	sf::Texture* xboxATexture;
	sf::Texture* xboxBTexture;
	sf::Texture* xboxXTexture;
	sf::Texture* xboxYTexture;
	sf::Texture* xboxMenuTexture;
	sf::Texture* xboxWindowTexture;
};