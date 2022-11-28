#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "TextureHolder.h"
#include "SmallEnemy.h"
#include "FloatingObstacle.h"
#include "GroundObstacle.h"

class Generator {
private:
	GroundObstacle m_groundObstacle;
	FloatingObstacle m_floatingObstacle;
	SmallEnemy m_smallEnemy;
public:
	void Generate();
};
