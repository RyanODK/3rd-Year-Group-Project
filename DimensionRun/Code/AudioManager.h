#pragma once
#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer> {
public:
	AudioManager() : ResourceManager("Code/Resources/audio.cfg") {}

	sf::SoundBuffer* Load(const std::string& l_Path) {
		sf::SoundBuffer* sound = new sf::SoundBuffer();

		if (!sound->loadFromFile(l_Path)) {
			delete sound;
			sound = nullptr;
			std::cerr << "!Failed to load sound: " << l_Path << std::endl;
		}
		return sound;
	}
};