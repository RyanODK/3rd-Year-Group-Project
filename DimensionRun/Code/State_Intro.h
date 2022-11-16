#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "SoundManager.h"

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

	SoundManager* GetSoundManager() {
		return &m_SoundManager;
	}

private:
	sf::Text m_MainTitle;
	sf::Text m_Names;
	sf::Text m_continueText;
	sf::Font m_Font;

	float m_TimePassed;

	SoundManager m_SoundManager;
};
