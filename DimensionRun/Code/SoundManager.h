#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
public:
	SoundManager();

	void playIntroMusic();
	void playMainMenuMusic(); // plays main menu music
	void playInGameMusic(); // plays in game music
	void stopMainMenuMusic(); // stop main menu music
	void stopInGameMusic(); // stops in game music

private:
	sf::Music introMusic;
	sf::Music mainMenuMusic; // stores main menu music
	sf::Music inGameMusic; // stores in game music
};