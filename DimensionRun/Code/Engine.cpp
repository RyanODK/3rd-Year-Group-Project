#include "Engine.h"

Engine::Engine() : m_Window("Dimension Run", 
	sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),
	m_StateManager(&m_Context), m_EntityManager(&m_SystemManager, &m_TextureManager), m_SoundManager(&m_AudioManager)
{
	m_SystemManager.SetEntityManager(&m_EntityManager);

	m_Context.m_Wind = &m_Window;
	m_Context.m_EventManager = m_Window.GetEventManager();
	m_Context.m_TextureManager = &m_TextureManager;
	m_Context.m_EntityManager = &m_EntityManager;
	m_Context.m_SystemManager = &m_SystemManager;
	m_Context.m_AudioManager = &m_AudioManager;
	m_Context.m_SoundManager = &m_SoundManager;

	m_SystemManager.m_debugOverlay = &m_Context.m_DebugOverlay;
	m_StateManager.SwitchTo(StateType::Game);
}

Engine::~Engine() {}

void Engine::Render() {
	m_Window.BeginDraw();
	// Render here.
	m_StateManager.Draw();

	// Debug.
	if (m_Context.m_DebugOverlay.Debug()) {
		m_Context.m_DebugOverlay.Draw(m_Window.GetRenderWindow());
	}
	// End debug.

	m_Window.EndDraw();
}

sf::Time Engine::GetElapsed() {
	return m_Elapsed;
}

void Engine::RestartClock() {
	m_Elapsed = m_Clock.restart();
}

void Engine::LateUpdate() {
	m_StateManager.ProcessRequests();
	RestartClock();
}