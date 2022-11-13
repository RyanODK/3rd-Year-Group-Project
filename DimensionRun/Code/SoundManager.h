#include <SFML/Audio.hpp>
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

using namespace sf;

class SoundManager {
public:
	SoundManager();

	void playMainMenuMusic(); // plays main menu music
	void playInGameMusic(); // plays in game music
	void stopMainMenuMusic(); // stop main menu music
	void stopInGameMusic(); // stops in game music

private:
	Music mainMenuMusic; // stores main menu music
	Music inGameMusic; // stores in game music
	Music inGameMusic1;

};
#endif