// Includes important C++ libraries and headers
#include "Background.h"
#include "Player.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Make code easier to type with "using namespace"
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

	//// Create a texture to hold background graphic on the GPU
	//Texture textureBackground;

	//// Load background graphic into the texture
	//textureBackground.loadFromFile("Graphics/cyberpunk-street-files/PNG/cyberpunk-street.png");

	//// Create a sprite for background
	//Sprite spriteBackground;

	//// Attach the texture to the spriteBackground
	//spriteBackground.setTexture(textureBackground);

	//// Set the spriteBackground to cover the screen
	//spriteBackground.setPosition(0, 0);

	//// set scale of background to fit screen
	//spriteBackground.setScale(resolution.x / spriteBackground.getLocalBounds().width, 
	//	resolution.y / spriteBackground.getLocalBounds().height);

	Background background;
	Player player;
	
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

		//elapsedTime = clock.restart().asSeconds();

		player.spawn(resolution);

		// every 0.25 seconds 
		// change playerSprite idle animation
		player.updateAnimation(clock);

		/*
			Draw scene
		*/

		if (state == State::PLAYING) {
			window.clear();

			background.BackgroundScale(resolution);
			background.Update(deltaTime);
			background.Render(window);
			window.draw(player.getSprite());
		}

		if (state == State::PAUSED) {

		}
		
		window.display();
	}
	return 0;

}