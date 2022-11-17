#pragma once

#include "Window.h"
#include "StateManager.h"
#include "EventManager.h"

//#include "MediumEnemy.h"
//#include "LargeEnemy.h"

class Engine {
public:
	Engine(); // default constructor to set game resolution and ground height

	sf::Time GetElapsed(); // gets elapsed time in game
	void RestartClock(); // restarts elapsed clock 
	void LateUpdate();

	Window* GetWindow() {
		return &m_Window;
	};

	void update(); // function to update game per frame
	void draw(); // function to draw everything on screen

private:

	///* Medium Enemies */
	//MediumEnemy m_MediumEnemy1;
	//MediumEnemy m_MediumEnemy2;
	//MediumEnemy m_MediumEnemy3;

	///* Large Enemies */
	//LargeEnemy m_LargeEnemy1;
	//LargeEnemy m_LargeEnemy2;
	//LargeEnemy m_LargeEnemy3;

	//void checkCol(Player& player);

	Window m_Window;
	StateManager m_StateManager;
	SharedContext m_Context;

	sf::Clock m_Clock;
	sf::Time m_Elapsed;
};