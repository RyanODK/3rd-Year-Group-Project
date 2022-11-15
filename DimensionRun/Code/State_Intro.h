#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState{
public:
	State_Intro(StateManager* l_StateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void Continue(EventDetails* l_Details);

private:
	sf::Text m_MainTitle;
	sf::Text m_Names;
	sf::Text m_continueText;
	sf::Font m_Font;

	float m_TimePassed;
};
