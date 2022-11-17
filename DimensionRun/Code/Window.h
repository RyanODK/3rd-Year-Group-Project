#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window {
public:
	Window(); // Default constructor
	Window(const std::string& l_Title, // tracks window properties
		const sf::Vector2u& l_Size); // and calls Setup() function
	~Window(); // destructor contructor

	void BeginDraw(); // clear window
	void EndDraw(); // display changes

	void Update(); // this updates window taking in users input to execute 

	bool IsDone(); // returns true if window is done
	bool IsFullScreen(); // returns true if window is fullscreen
	sf::Vector2u GetWindowSize(); // gets window size

	void ToggleFullScreen(EventDetails* l_Details); // this toggles fullscreen mode

	void Draw(sf::Drawable& l_Drawable); // draws to window

	bool IsFocused(); // returns true if window is focused

	sf::RenderWindow* GetRenderWindow() {
		return &m_Window;
	}

	EventManager* GetEventManager() {
		return &m_EventManager;
	};

	void Close(EventDetails* l_Details = nullptr);

private:
	void Setup(const std::string& l_Title, // keeps track of window properties
		const sf::Vector2u& l_Size); // calls Create() function
	void Destroy(); // this will close window
	void Create(); // uses SFML Uint32 to initialise window style (We use Default style)
				   // Default style offers Title bar, resizable border, maximize and close buttons

	sf::RenderWindow m_Window;
	sf::Vector2u m_WindowSize;
	std::string m_WindowTitle;
	bool m_IsDone;
	bool m_IsFullScreen;
	EventManager m_EventManager;
	bool m_IsFocused;
};

