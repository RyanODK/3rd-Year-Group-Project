#include "Engine.h"

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event)) {
		if (state == State::MAIN_MENU) {
			// Handle player entering game
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}
			// handle player wanting to exit game
			if (event.key.code == Keyboard::Num2)
			{
				state = State::GAME_OVER;
			}
		}

		if (state == State::PAUSED)
		{
			// handle player wanting to resume game
			if (event.key.code == Keyboard::R)
			{
				state = State::PLAYING;
			}
			// handle player wanting to exit game
			if (event.key.code == Keyboard::E)
			{
				state = State::GAME_OVER;
			}
		}
		// close window if game over
		if (state == State::GAME_OVER) {
			m_Window.close();
		}

		if (state == State::PLAYING) {
			// escape will bring user to main menu
			if (event.key.code == (Keyboard::Escape))
			{
				state = State::MAIN_MENU;
			}
			// backspace will pause users game
			if (event.key.code == (Keyboard::Backspace))
			{
				state = State::PAUSED;
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		m_player.Jump();
	}
}