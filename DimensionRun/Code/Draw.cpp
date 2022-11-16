#include "Engine.h"

void Engine::draw() {
	m_Window.BeginDraw();
	m_StateManager.Draw();
	m_Window.EndDraw();
}
