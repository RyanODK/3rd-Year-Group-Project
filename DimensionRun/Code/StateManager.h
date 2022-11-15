#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include <SFML/Graphics.hpp>
//#include "BaseState.h"
#include "State_Intro.h"

enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

struct SharedContext {
	SharedContext() :m_Wind(nullptr), m_EventManager(nullptr) {}
	sf::Window* m_Wind;
	EventManager* m_EventManager;
};

using StateContainer = vector<pair<StateType, BaseState*>>;

using TypeContainer = vector<StateType>;

using StateFactory = unordered_map<StateType,
	function<BaseState*(void)>>;

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
#endif