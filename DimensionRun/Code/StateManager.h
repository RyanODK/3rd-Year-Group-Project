#pragma once
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_GameOver.h"
#include "State_Paused.h"
#include "State_Credits.h"
#include "SharedContext.h"
#include <vector>
#include <unordered_map>

// all possible States the game could be in for now
enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

// this is a container of a vector for the used Statetype and a pointer to the BaseState class
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

// this is a vector of all the StateType enum types
using TypeContainer = std::vector<StateType>;

// this produces objects of different types derived from BaseClass
using StateFactory = std::unordered_map<StateType,
	std::function<BaseState*(void)>>;

class StateManager {
public:
	StateManager(SharedContext* l_Shared); // this is where we register states using RegisterState()
	~StateManager(); // this destructor will iterate over the states and delete if needed

	/*
		Update() will check if the top state allows other stats to be updates
		these other states will then have their Update() methods invoked using deltaTime

		
		Draw() checks if the state container has at least one state
		if this is true then it checks the most recent added transparency flag 
		and if there is more than one state on the stack
		if there is only one state on the stack OR the current state isn't transparent 
		then invoke the Draw() method
	*/
	void Update(const sf::Time& l_Time);
	void Draw();

	// this iterates over the m_ToRemove vector and invokes the method RemoveState()
	// this will take care of resource de-allocation
	void ProcessRequests(); 

	/*
		GetContext() returns a pointer to the m_Shared member

		HasState() iterates over the m_States container 
		until it finds a state with type l_Type and returns true
		if it doesnt find a state like this or if the found state is about to be removed
		it returns false
		this will check if a state is on the stack
	*/
	SharedContext* GetContext();
	bool HasState(const StateType& l_Type);

	void SwitchTo(const StateType& l_Type); // this will switch states when called
	void Remove(const StateType& l_Type); // this will remove a state from the state stack
private:
	/*
		CreateState() using m_StateFactory as an iterator 
		checks if a state with such type can be created
		if it can then a pointer of BaseState called state is created
		and returns a pointer to a newly created state class
		then it pushes this new state into the state vector and calls OnCreate() from BaseState

		RemoveState() will iterate over the state vector to check for a matching state
		if a match is found then it uses OnDestroy() from BaseClass to remove the state
	*/
	void CreateState(const StateType& l_Type);
	void RemoveState(const StateType& l_Type);

	/*
		This will create states and add them to the heap
		StateFactory is used to map a link between a state type and a function type
		this will hold a body of a function using the lambda expression
	*/
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