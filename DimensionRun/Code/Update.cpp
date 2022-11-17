#include "Engine.h"

void Engine::update() {
	m_Window.Update();
	m_StateManager.Update(m_Elapsed);

	// checkCol(m_player);
}