#include "Engine.h"

void Engine::update() {
	m_Window.Update();
	m_StateManager.Update(m_Elapsed);
	m_SoundManager.Update(m_Elapsed.asSeconds());
	// checkCol(m_player);
}