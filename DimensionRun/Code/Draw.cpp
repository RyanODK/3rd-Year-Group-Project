#include "Engine.h"

void Engine::draw() {
	m_Window.clear();

	if (state == State::PLAYING) {
		//window.setFramerateLimit(60);
		m_Window.draw(m_background.getSprite());
		m_Window.draw(m_player.getSprite());
		//window.draw(enemy.getSprite());
	}

	if (state == State::MAIN_MENU)
	{
		// Draw the main menu
		m_Window.draw(spriteMainMenu);
		m_Window.draw(mainMenuText);
	}

	if (state == State::PAUSED)
	{
		// Draw the pause menu
		m_Window.draw(spriteMainMenu);
		m_Window.draw(pauseMenuText);
	}

	m_Window.display();
}
