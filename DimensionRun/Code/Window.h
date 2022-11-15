//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"

//using namespace std;
//using namespace sf;

class Window {
public:
	Window();
	Window(const std::string& l_Title, const
		sf::Vector2u& l_Size);
	~Window();

	void BeginDraw(); // clear window
	void EndDraw(); // display changes

	void Update();

	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullScreen(EventDetails* l_Details);

	void Draw(sf::Drawable& l_Drawable);

	bool IsFocused();

	sf::RenderWindow* GetRenderWindow() {
		return &m_Window;
	}

	EventManager* GetEventManager() {
		return &m_EventManager;
	};

	void Close(EventDetails* l_Details = nullptr);

private:
	void Setup(const std::string& l_Title,
		const sf::Vector2u& l_Size);
	void Destroy();
	void Create();

	sf::RenderWindow m_Window;
	sf::Vector2u m_WindowSize;
	std::string m_WindowTitle;
	bool m_IsDone;
	bool m_IsFullScreen;
	EventManager m_EventManager;
	bool m_IsFocused;
};

