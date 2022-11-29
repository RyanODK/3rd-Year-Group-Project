#pragma once
#include "EventManager.h"

// forward declaration of StateManager class to keep pointer of it
// also avoids recursive definitions
class StateManager; 

class BaseState {
	friend class StateManager;

public:
	BaseState(StateManager* l_StateManager) :
		m_StateMgr(l_StateManager), m_Transparent(false),
		m_Transcendent(false) {}

	/* 
		These virtual functions need to be implemented in the inheriting state classes
		for example State_Game needs to include all these virtual fucntions 
		or else project wont compile!
	*/
	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& deltaTime) = 0;
	virtual void Draw() = 0;

	void SetTransparent(const bool& l_Transparent) {
		m_Transparent = l_Transparent;
	}

	bool IsTransparent() const {
		return m_Transparent;
	}

	void SetTranscendent(const bool& l_Transcendent) {
		m_Transcendent = l_Transcendent;
	}

	bool IsTranscendent() const {
		return m_Transcendent;
	}

	sf::View& GetView() { 
		return m_View; 
	}

	StateManager* GetStateManager() {
		return m_StateMgr;
	}

protected:
	StateManager* m_StateMgr;

	// these flags will check if state needs to render or update state that came before it
	// eliminates need of countless enumerations for transitions between states
	bool m_Transparent;
	bool m_Transcendent;
	sf::View m_View;
};
