#include "Engine.h"

Engine::Engine() : m_Window("Dimension Run", 
	sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),
	m_StateManager(&m_Context)
{
	m_Context.m_Wind = &m_Window;
	m_Context.m_EventManager = m_Window.GetEventManager();
	m_StateManager.SwitchTo(StateType::Game);
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