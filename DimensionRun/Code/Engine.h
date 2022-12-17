#pragma once
#include "Window.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include <iostream>

class Engine {
public:
	Engine(); // default constructor to set game resolution and ground height
	~Engine();

	sf::Time GetElapsed(); // gets elapsed time in game
	void LateUpdate();

	Window* GetWindow() {
		return &m_Window;
	};

	void update(); // function to update game per frame
	void draw(); // function to draw everything on screen

private:
	void RestartClock(); // restarts elapsed clock 
	Window m_Window;
	StateManager m_StateManager;
	SharedContext m_Context;

	sf::Clock m_Clock;
	sf::Time m_Elapsed;

	EntityManager m_EntityManager;
	TextureManager m_TextureManager;
	AudioManager m_AudioManager;
	SoundManager m_SoundManager;
	FontManager m_FontManager;
	GUI_Manager m_GuiManager;
};