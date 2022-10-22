// Includes important C++ libraries and headers
#include "Engine.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Makes code easier to type with "using namespace"
using namespace sf;

int main()
{
	// bring in engine class to main
	Engine engine;

	// run game from engine
	engine.run();

	return 0;
}