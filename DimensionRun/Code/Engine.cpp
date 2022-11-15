#include "Engine.h"

Engine::Engine() : m_Window("Dimension Run", 
	sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),
	m_StateManager(&m_Context)
{
	m_Context.m_Wind = &m_Window;
	m_Context.m_EventManager = m_Window.GetEventManager();
	m_StateManager.SwitchTo(StateType::Intro);

	//// set dimension of screen using users desktop resolution
	//Vector2f resolution;
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	//// Create and open a window for the game titled Dimension Run
	//m_Window.create(VideoMode(resolution.x, resolution.y),
	//	"Dimension Run", Style::Fullscreen);

	//// sets groundheight to 75% of screen resolution
	//groundHeight = (resolution.y / 100) * 75;

	//// load font
	//font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");

	//// set font for main menu text
	//mainMenuText.setFont(font);
	//// set character size
	//mainMenuText.setCharacterSize(80);
	//// set color of text to white
	//mainMenuText.setFillColor(Color::White);
	//// set position of text on screen
	//mainMenuText.setPosition(500, 250);
	//// declare stringstream for text
	//std::stringstream mainMenuStream;
	//// initialise main menu options
	//mainMenuStream <<
	//	"Dimension Run" <<
	//	"\n1 - Play Game" <<
	//	"\n2 - Exit ";
	//// set mainMenuText from stringstream 
	//mainMenuText.setString(mainMenuStream.str());

	//// pause menu options
	//pauseMenuText.setFont(font);
	//pauseMenuText.setCharacterSize(80);
	//pauseMenuText.setFillColor(Color::White);
	//pauseMenuText.setPosition(500, 250);
	//std::stringstream pauseMenuStream;
	//pauseMenuStream <<
	//	"Game Paused " <<
	//	"\nR - Resume" <<
	//	"\nE - Exit Game";

	//pauseMenuText.setString(pauseMenuStream.str());

	//m_resolution = resolution;
	//m_SoundManager.playInGameMusic();
}

sf::Time Engine::GetElapsed() {
	return m_Elapsed;
}

void Engine::RestartClock() {
	m_Elapsed = m_Clock.restart();
}

void Engine::LateUpdate() {
	m_StateManager.ProcessRequests();
	RestartClock();
}

void Engine::run() {
	//Clock clock; // clock to store time in game

	while (!GetWindow()->IsDone()) {
		// pauses game if in pause or main menu screen
		/*if (state == State::PAUSED || state == State::MAIN_MENU) {
			clock.restart();
		}*/
		//		
		//Time dt = clock.restart();

		//m_GameTimeTotal += dt;

		//float dtAsSeconds = dt.asSeconds();

		//if (state == State::PLAYING) {
		//	distanceRan += dtAsSeconds;

		//	/*if (distanceRan > bestDistance) {
		//		bestDistance = distanceRan;
		//	}*/
		//}

		//resetTime += dtAsSeconds;

		//// current distance text
		//distanceText.setFont(font);
		//distanceText.setCharacterSize(70);
		//distanceText.setFillColor(Color::White);
		//distanceText.setPosition(0, 0);
		//stringstream distanceStream;
		//distanceStream.precision(0); // no decimal places
		//// fixed will keep it as numbers rather than scientific notation
		//distanceStream << fixed <<
		//	distanceRan <<
		//	"m";

		//distanceText.setString(distanceStream.str());

		//// best distance text
		//bestDistanceText.setFont(font);
		//bestDistanceText.setCharacterSize(35);
		//bestDistanceText.setFillColor(Color::White);
		//bestDistanceText.setPosition(0, 70);
		//stringstream bestDistanceStream;
		//bestDistanceStream.precision(0);
		//bestDistanceStream << fixed <<
		//	"Best: " <<
		//	bestDistance <<
		//	"m";

		//bestDistanceText.setString(bestDistanceStream.str());

		//// coin count text
		//coinCountText.setFont(font);
		//coinCountText.setCharacterSize(50);
		//coinCountText.setFillColor(Color::Yellow);
		//coinCountText.setPosition(0, 105);
		//stringstream coinStream;
		//coinStream.precision(0);
		//coinStream << fixed <<
		//	coinCount;

		//coinCountText.setString(coinStream.str());

		//input();
		update();
		draw();
		sf::sleep(sf::seconds(0.2)); // sleep for 0.2 seconds
		LateUpdate();
	}
}