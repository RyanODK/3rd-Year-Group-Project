#include <SFML/Graphics.hpp>
#include "EventManager.h"
#ifndef WINDOW_H
#define WINDOW_H

using namespace std;
//using namespace sf;

class Window {
public:
	Window();
	Window(const string& l_Title, const
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
	EventManager* GetEventManager();
	void Close(EventDetails* l_Details = nullptr);

private:
	void Setup(const string& l_Title,
		const sf::Vector2u& l_Size);
	void Destroy();
	void Create();

	sf::RenderWindow m_Window;
	sf::Vector2u m_WindowSize;
	string m_WindowTitle;
	bool m_IsDone;
	bool m_IsFullScreen;
	EventManager m_EventManager;
	bool m_IsFocused;
};
#endif

