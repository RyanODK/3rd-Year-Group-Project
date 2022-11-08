#include "Engine.h"

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event)) {
		if (state == State::MAIN_MENU) {
			if (event.type == Event::KeyPressed)
			{
				//m_SoundManager.stopInGameMusic();
				//m_SoundManager.playMainMenuMusic();
				// Handle player entering game
				if (Keyboard::isKeyPressed(Keyboard::Num1))
				{
					state = State::PLAYING;
				}
				// handle player wanting to exit game
				if (Keyboard::isKeyPressed(Keyboard::Num2))
				{
					state = State::GAME_OVER;
				}

				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					state = State::GAME_OVER;
				}
			}
		}

		if (state == State::PAUSED)
		{
			if (event.type == Event::KeyPressed)
			{
				//m_SoundManager.stopInGameMusic();
				// handle player wanting to resume game
				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					state = State::PLAYING;
				}
				// handle player wanting to exit game
				if (Keyboard::isKeyPressed(Keyboard::E))
				{
					state = State::GAME_OVER;
				}
			}
		}

		// close window if game over
		if (state == State::GAME_OVER) {
			m_Window.close();
		}

		if (state == State::PLAYING) {
			if (event.type == Event::KeyPressed)
			{
				//m_SoundManager.stopMainMenuMusic();
				//m_SoundManager.playInGameMusic();
				// escape will bring user to main menu
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					state = State::MAIN_MENU;
				}
				// backspace will pause users game
				if (Keyboard::isKeyPressed(Keyboard::Backspace))
				{
					state = State::PAUSED;
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && canJump) {
		m_player.Jump();
		canJump = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::C) && canSlide) {
		m_player.Slide();
		canSlide = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::X) && canLaser) {
		m_player.Laser();
		canLaser = false;
	}

	if (!canJump) {
		jumpInterval += m_GameTimeTotal.asSeconds();

		if (jumpInterval >= 40000) {
			jumpInterval = 0.0f;
			canJump = true;
		}
	}

	if (!canSlide) {
		slideInterval += m_GameTimeTotal.asSeconds();

		if (slideInterval >= 40000) {
			slideInterval = 0.0f;
			canSlide = true;
		}
	}

	if (!canLaser) {
		laserInterval += m_GameTimeTotal.asSeconds();

		if (laserInterval >= 40000) {
			laserInterval = 0.0f;
			canLaser = true;
		}
	}
}