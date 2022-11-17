#pragma once
#include "Window.h"
#include "EventManager.h"

// this is a pointer to the most commonly used classes
struct SharedContext {
	SharedContext() :
		m_Wind(nullptr), 
		m_EventManager(nullptr) {}

	Window* m_Wind;
	EventManager* m_EventManager;
};
