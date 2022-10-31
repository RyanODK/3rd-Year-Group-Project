#include "Engine.h"

Engine::Engine() {
	// set dimension of screen using users desktop resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Create and open a window for the game titled Dimension Run
	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Dimension Run", Style::Fullscreen);

	// sets groundheight depending on resolution
	if (resolution.x == 2560 && resolution.y == 1440) {
		groundHeight = 1080;
	}
	else if (resolution.x == 1920 && resolution.y == 1080) {
		groundHeight = 850;
	}
	else if (resolution.x == 1680 && resolution.y == 1050) {
		groundHeight = 800;
	}

	// load font
	font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");

	// set font for main menu text
	mainMenuText.setFont(font);
	// set character size
	mainMenuText.setCharacterSize(80);
	// set color of text to white
	mainMenuText.setFillColor(Color::White);
	// set position of text on screen
	mainMenuText.setPosition(500, 250);
	// declare stringstream for text
	std::stringstream mainMenuStream;
	// initialise main menu options
	mainMenuStream <<
		"Dimension Run" <<
		"\n1 - Play Game" <<
		"\n2 - Exit ";
	// set mainMenuText from stringstream 
	mainMenuText.setString(mainMenuStream.str());

	// pause menu options
	pauseMenuText.setFont(font);
	pauseMenuText.setCharacterSize(80);
	pauseMenuText.setFillColor(Color::White);
	pauseMenuText.setPosition(500, 250);
	std::stringstream pauseMenuStream;
	pauseMenuStream <<
		"Game Paused " <<
		"\nR - Resume" <<
		"\nE - Exit Game";

	pauseMenuText.setString(pauseMenuStream.str());

	m_resolution = resolution;
}

void Engine::run() {
	Clock clock; // clock to store time in game

	while (m_Window.isOpen()) {
		Time dt = clock.restart();

		m_GameTimeTotal += dt;

		float dtAsSeconds = dt.asSeconds();

		distanceRan += dtAsSeconds;

		distanceText.setFont(font);
		distanceText.setCharacterSize(80);
		distanceText.setFillColor(Color::White);
		distanceText.setPosition(100, 250);
		stringstream distanceStream;
		distanceStream <<
			distanceRan <<
			"m";

		distanceText.setString(distanceStream.str());

		input();
		update(dtAsSeconds);
		draw();
	}
}