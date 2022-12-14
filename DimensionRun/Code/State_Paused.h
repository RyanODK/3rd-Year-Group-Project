#pragma once
#include "BaseState.h"
#include "EventManager.h"
//#include "Background.h"
#include "TextureHolder.h"

class State_Paused : public BaseState {
public:
	State_Paused(StateManager* l_StateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void Unpause(EventDetails* l_Details);

private:
	sf::Font m_Font;
	sf::Text m_PausedText;
	sf::RectangleShape m_Rect;
};
