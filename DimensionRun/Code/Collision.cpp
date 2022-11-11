#include "Engine.h"
#include <iostream>

void Engine::checkCol(Player& player)
{
	FloatRect detectionZone = m_player.getGlobal();

	// depending on resolution set position and scale of player
	if (player.getGlobal().intersects(m_obstacle.getGlobal()))
	{
		//state = State::PAUSED;
		cout << "Colliding " << "\n";
	}
	else {
		cout << "Not Colliding" << "\n";
	}
}