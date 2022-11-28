#include "State_Game.h"

void State_Game::CheckCol()
{
	if (GetPlayer()->getPositionY() >= groundHeight && !GetPlayer()->Jump()) {
		GetPlayer()->setFalling(false);
		//std::cout << "Grounded" << std::endl;
	}
	else {
		//std::cout << "IT WORKS " << std::endl;
	}
//
//	if (player.getRight().intersects(m_floatingObstacle.getGlobal())) {
//		cout << "colliding on right side" << endl;
//		m_floatingObstacle.update(distanceRan);
//	}
}