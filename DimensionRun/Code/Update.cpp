#include "Engine.h"

void Engine::update() {
	m_Window.Update();
	m_StateManager.Update(m_Elapsed);
	m_SoundManager.Update(m_Elapsed.asSeconds());
	m_GuiManager.Update(m_Elapsed.asSeconds());
	
	GUI_Event guiEvent;
	while (m_Context.m_GuiManager->PollEvent(guiEvent)) {
		m_Window.GetEventManager()->HandleEvent(guiEvent);
	}
}