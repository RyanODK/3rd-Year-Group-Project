#include "Engine.h"
#include <iostream>

void Engine::checkCol(Player& player)
{
	if (player.getRight().intersects(m_groundObstacle.getGlobal())) {
		cout << "colliding on right side" << endl;
		m_groundObstacle.update(distanceRan);
	}
	if (player.getRight().intersects(m_floatingObstacle.getGlobal())) {
		cout << "colliding on right side" << endl;
		m_floatingObstacle.update(distanceRan);
	}
}