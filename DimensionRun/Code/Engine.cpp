#include "Engine.h"

Engine::Engine() : m_Window("Dimension Run", 
	sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),
	m_StateManager(&m_Context), m_EntityManager(&m_Context, 100),
	m_SoundManager(&m_AudioManager), m_GuiManager(m_Window.GetEventManager(), &m_Context)
{
	m_Clock.restart();
	srand(time(nullptr));

	m_Context.m_Wind = &m_Window;
	m_Context.m_EventManager = m_Window.GetEventManager();
	m_Context.m_TextureManager = &m_TextureManager;
	m_Context.m_EntityManager = &m_EntityManager;
	m_Context.m_AudioManager = &m_AudioManager;
	m_Context.m_SoundManager = &m_SoundManager;
	m_Context.m_FontManager = &m_FontManager;
	m_Context.m_GuiManager = &m_GuiManager;

	m_FontManager.RequireResource("Main");
	m_StateManager.SwitchTo(StateType::MainMenu);
}

Engine::~Engine() {
	m_FontManager.ReleaseResource("Main");
}

sf::Time Engine::GetElapsed() {
	return m_Clock.getElapsedTime();
}

void Engine::RestartClock() {
	m_Elapsed = m_Clock.restart();
}

void Engine::LateUpdate() {
	m_StateManager.ProcessRequests();
	RestartClock();
}