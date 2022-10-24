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

	m_resolution = resolution;
}

void Engine::run() {
	Clock clock; // clock to store time in game

	while (m_Window.isOpen()) {
		Time dt = clock.restart();

		m_GameTimeTotal += dt;

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}