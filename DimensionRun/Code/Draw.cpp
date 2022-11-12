#include "Engine.h"

void Engine::draw() {
	m_Window.clear();

	if (state == State::PLAYING) {
		//window.setFramerateLimit(60);
		m_Window.draw(m_background.getSprite1());
		m_Window.draw(m_background.getSprite2());
		m_Window.draw(m_background.getSprite3());

		m_Window.draw(m_player.getSprite());
		m_Window.draw(m_obstacle.getSprite());
		m_Window.draw(m_SmallEnemy1.getSprite());

		m_Window.draw(distanceText);
	}

	if (state == State::MAIN_MENU)
	{
		// Draw the main menu
		m_Window.draw(m_mainMenuBackground.getSprite1());
		m_Window.draw(m_mainMenuBackground.getSprite2());
		m_Window.draw(m_mainMenuBackground.getSprite3());
		m_Window.draw(mainMenuText);
	}

	if (state == State::PAUSED)
	{
		// Draw the pause menu
		m_Window.draw(m_mainMenuBackground.getSprite1());
		m_Window.draw(m_mainMenuBackground.getSprite2());
		m_Window.draw(m_mainMenuBackground.getSprite3());
		m_Window.draw(pauseMenuText);
	}

	m_Window.display();
}