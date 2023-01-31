#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class State_MainMenu : public BaseState {
public:
	State_MainMenu(StateManager* l_StateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_Time);
	void Draw();

	void Play(EventDetails* l_Details);
	void Credits(EventDetails* l_Details);
	void Quit(EventDetails* l_Details);

private:
	sf::SoundBuffer buttonBuffer;
	sf::Sound buttonSound;

	std::string textureString;
	sf::Sprite XboxA;

	sf::Texture* texture;
	sf::Vector2f m_ScaleFactors;
};