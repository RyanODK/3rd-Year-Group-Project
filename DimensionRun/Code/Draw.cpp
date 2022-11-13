#include "Engine.h"

void Engine::draw() {
	m_Window.clear();

	if (state == State::PLAYING) {
		//window.setFramerateLimit(60);
		m_Window.draw(m_background.getSprite1());
		m_Window.draw(m_background.getSprite2());
		m_Window.draw(m_background.getSprite3());

		m_Window.draw(m_player.getSprite());
		m_Window.draw(m_groundObstacle.getSprite());
		m_Window.draw(m_floatingObstacle.getSprite());

		m_Window.draw(m_Portal.getSprite());

		if (backgroundType == 1) {
			m_Window.draw(m_SmallEnemy1.getSprite());
		}

		if (backgroundType == 2) {
			m_Window.draw(m_SmallEnemy2.getSprite());
		}

		if (backgroundType == 3) {
			m_Window.draw(m_SmallEnemy3.getSprite());
		}

		if (backgroundType == 4) {
			m_Window.draw(m_SmallEnemy4.getSprite());
		}

		if (backgroundType == 5) {
			m_Window.draw(m_SmallEnemy5.getSprite());
		}

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
