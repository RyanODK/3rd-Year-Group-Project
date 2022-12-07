#include "Engine.h"

void Engine::draw() {
	m_Window.BeginDraw();
	// Render here.
	m_StateManager.Draw();

	sf::View CurrentView = m_Window.GetRenderWindow()->getView();
	m_Window.GetRenderWindow()->setView(m_Window.GetRenderWindow()->getDefaultView());
	m_GuiManager.Render(m_Window.GetRenderWindow());
	m_Window.GetRenderWindow()->setView(CurrentView);

	// Debug.
	if (m_Context.m_DebugOverlay.Debug()) {
		m_Context.m_DebugOverlay.Draw(m_Window.GetRenderWindow());
	}
	// End debug.

	m_Window.EndDraw();
}
