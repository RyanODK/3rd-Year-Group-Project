#include "SoundManager.h"

SoundManager::SoundManager() {
	// music for main menu
	mainMenuMusic.openFromFile(
		"Sound/cyberpunk music/MainMenu/cyberpunk-street.wav");
	mainMenuMusic.setLoop(true);
	mainMenuMusic.setVolume(20);

	// music for in game
	/*inGameMusic.openFromFile(
		"Sound/cyberpunk music/InGameSounds/DavidKBD - Pink Bloom Pack - 01 - Pink Bloom.ogg");*/
	inGameMusic.openFromFile(
		"Sound/cyberpunk music/InGameSounds/cyber city 2-b.ogg");
	inGameMusic.setLoop(true);
	inGameMusic.setVolume(20);
}

void SoundManager::playMainMenuMusic() {
	mainMenuMusic.play(); // play in game music
}

void SoundManager::playInGameMusic() {
	inGameMusic.play(); // play in game music
}

void SoundManager::stopMainMenuMusic() {
	mainMenuMusic.stop();
}

void SoundManager::stopInGameMusic() {
	inGameMusic.stop();
}