#pragma once
#include "Window.h"
#include "EventManager.h"

struct SharedContext {
	SharedContext() :
		m_Wind(nullptr), 
		m_EventManager(nullptr) {}

	Window* m_Wind;
	EventManager* m_EventManager;
};
