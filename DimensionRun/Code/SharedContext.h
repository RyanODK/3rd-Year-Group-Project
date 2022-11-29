#pragma once
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "Map.h"

// this is a pointer to the most commonly used classes
struct SharedContext {
	SharedContext() :
		m_Wind(nullptr), 
		m_EventManager(nullptr),
		m_TextureManager(nullptr),
		m_EntityManager(nullptr),
		m_GameMap(nullptr) {}

	Window* m_Wind;
	EventManager* m_EventManager;
	TextureManager* m_TextureManager;
	EntityManager* m_EntityManager;
	Map* m_GameMap;
};
