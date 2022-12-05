#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "Background.h"
#include "TextureHolder.h"

class State_MainMenu : public BaseState {
public:
	State_MainMenu(StateManager* l_StateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void MouseClick(EventDetails* l_Details);

	Background* GetBackground() {
		return &m_mainMenuBackground;
	};

	void Play(EventDetails* l_Details);
	void Credits(EventDetails* l_Details);
	void QuitGame(EventDetails* l_Details);

private:
	sf::Font m_Font;

	sf::Text m_MainTitle;
	
	sf::Vector2f m_ButtonSize;
	sf::Vector2f m_ButtonPos;
	unsigned int m_ButtonPadding;

	sf::RectangleShape m_Rects[3];
	sf::Text m_Options[3];

	Background m_mainMenuBackground;
	TextureHolder m_TextureHolder;
};