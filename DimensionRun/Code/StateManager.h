#pragma once
//#include <SFML/Graphics.hpp>
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_GameOver.h"
#include "State_Paused.h"
#include "State_Credits.h"
#include "SharedContext.h"

enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType,
	std::function<BaseState*(void)>>;

class StateManager {
public:
	StateManager(SharedContext* l_Shared);
	~StateManager();

	void Update(const sf::Time& l_Time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& l_Type);

	void SwitchTo(const StateType& l_Type);
	void Remove(const StateType& l_Type);
private:
	void CreateState(const StateType& l_Type);
	void RemoveState(const StateType& l_Type);

	template <class T>
	void RegisterState(const StateType& l_Type) {
		m_StateFactory[l_Type] = [this]() -> BaseState* {
			return new T(this);
		};
	}

	SharedContext* m_Shared;
	StateContainer m_States;
	TypeContainer m_ToRemove;
	StateFactory m_StateFactory;
};