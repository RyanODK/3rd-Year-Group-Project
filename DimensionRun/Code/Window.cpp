#include "Window.h"

Window::Window() {
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& l_Title,
	const sf::Vector2u& l_Size) {
	Setup(l_Title, l_Size);
}

Window::~Window() {
	Destroy();
}

void Window::Destroy() {
	m_Window.close();
}

void Window::Setup(const std::string& l_Title,
	const sf::Vector2u& l_Size) {
	m_WindowTitle = l_Title;
	m_WindowSize = l_Size;
	m_IsFullScreen = false;
	m_IsDone = false;

	m_IsFocused = true; // default value for focused flag
	m_EventManager.AddCallback(StateType(0), "Fullscreen_toggle",
		&Window::ToggleFullScreen, this);

	Create();
}

void Window::Create() {
	auto style = (m_IsFullScreen ? sf::Style::Fullscreen :
		sf::Style::Default);
	m_Window.create({
		m_WindowSize.x, m_WindowSize.y, 32 },
		m_WindowTitle, style);
}

void Window::Update() {
	sf::Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_IsFocused = false;
			m_EventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_IsFocused = true;
			m_EventManager.SetFocus(true);
		}
		m_EventManager.HandleEvent(event);
	}
	m_EventManager.Update();
}

void Window::ToggleFullScreen(EventDetails* l_Details) {
	m_IsFullScreen = !m_IsFullScreen;
	Destroy();
	Create();
}

void Window::BeginDraw() {
	m_Window.clear(sf::Color::Black);
}

void Window::EndDraw() {
	m_Window.display();
}

bool Window::IsDone() {
	return m_IsDone;
}

bool Window::IsFullScreen() {
	return m_IsFullScreen;
}

bool Window::IsFocused() { 
	return m_IsFocused; 
}

sf::Vector2u Window::GetWindowSize() {
	return m_WindowSize;
}

void Window::Draw(sf::Drawable& l_Drawable) {
	m_Window.draw(l_Drawable);
}

void Window::Close(EventDetails* l_Details) {
	m_IsDone = true;
}