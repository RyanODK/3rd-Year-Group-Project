#pragma once
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "DebugOverlay.h"
#include "AudioManager.h"
#include "SoundManager.h"
#include "SystemManager.h"

// this is a pointer to the most commonly used classes
class Map;
struct SharedContext {
	SharedContext() :
		m_Wind(nullptr), 
		m_EventManager(nullptr),
		m_TextureManager(nullptr),
		m_EntityManager(nullptr),
		m_AudioManager(nullptr),
		m_SoundManager(nullptr),
		m_SystemManager(nullptr),
		m_GameMap(nullptr) {}

	Window* m_Wind;
	EventManager* m_EventManager;
	TextureManager* m_TextureManager;
	EntityManager* m_EntityManager;
	Map* m_GameMap;
	AudioManager* m_AudioManager;
	SoundManager* m_SoundManager;
	SystemManager* m_SystemManager;
	DebugOverlay m_DebugOverlay;
};
