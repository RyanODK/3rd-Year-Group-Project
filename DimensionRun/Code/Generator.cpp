#include "Generator.h"

void Generator::Generate() {
	
	int rAnD = (std::rand() % 3) + 1;

	switch (rAnD) {
	case(1):
		if (m_groundObstacle.getActive() == false) {
			m_groundObstacle.setActive(true);
		}
		break;
	case(2):
		if (m_floatingObstacle.getActive() == false) {
			m_floatingObstacle.setActive(true);
		}
		break;
	case(3):
		if (m_smallEnemy.getActive() == false) {
			m_smallEnemy.setActive(true);
		}
		break;
	default:
		break;
	}
}