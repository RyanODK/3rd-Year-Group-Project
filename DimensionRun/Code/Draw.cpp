#include "Engine.h"

void Engine::draw() {
	m_Window.clear();

	//window.setFramerateLimit(60);
	m_Window.draw(m_background.getSprite());
	m_Window.draw(m_player.getSprite());
	//window.draw(enemy.getSprite());

	m_Window.display();
}
