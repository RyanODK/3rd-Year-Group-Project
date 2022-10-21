// Includes important C++ libraries and headers
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "TextureHolder.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Makes code easier to type with "using namespace"
using namespace sf;

int main()
{
	// enum classes for state of game
	enum class State {
		PLAYING, PAUSED, GAME_OVER
	};

	// start with PAUSED state
	State state = State::PAUSED;

	// set dimension of screen using users desktop resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Create and open a window for the game titled Dimension Run
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Dimension Run", Style::Fullscreen);

	Background background;
	Player player;
	Enemy enemy;
	
	// clock to time everything in game
	Clock clock;
	Time deltaTime;
	float elapsedTime = 0.0f;

	while (window.isOpen()) {

		/*
		*************
		Handle inputs
		*************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				// to pause game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state == State::PAUSED;
				}
				// Restart game while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;

					Time currentTime = clock.restart();
					deltaTime = currentTime;
					elapsedTime = deltaTime.asSeconds();
				}
				/*else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::PLAYING
				}*/
			}

			if (event.type == Event::EventType::Closed) {
				window.close();
			}
		}

		// Handles player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		player.spawn(resolution, elapsedTime);
		player.update();
		//enemy.spawn(resolution, elapsedTime);
		//enemy.update();
		background.BackgroundScale(resolution);
		background.Update(deltaTime);


		/*
			Draw scene
		*/

		if (state == State::PLAYING) {
			window.clear();

			background.Render(window);
			window.draw(player.getSprite());
			//window.draw(enemy.getSprite());
		}

		if (state == State::PAUSED) {

		}
		
		window.display();
	}
	return 0;
}