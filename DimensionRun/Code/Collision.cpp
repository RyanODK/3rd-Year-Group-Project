#include "Engine.h"
#include <iostream>

void Engine::checkCol(Player& player)
{
	if (player.getRight().intersects(m_obstacle.getGlobal())) {
		cout << "colliding on right side" << endl;
		m_obstacle.update(distanceRan);
	}
}