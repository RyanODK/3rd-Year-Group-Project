#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

using namespace std;

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {
	EventInfo() {
		m_Code = 0;
	}
	EventInfo(int l_Event) {
		m_Code = l_Event;
	}
	union {
		int m_Code;
	};
};

using Events = vector<pair<EventType, EventInfo>>;

struct EventDetails {
	EventDetails(const string& l_BindName) :
		m_Name(l_BindName) {

		Clear();
	}
	string m_Name;

	sf::Vector2i m_Size;
	sf::Uint32 m_TextEntered;
	sf::Vector2i m_Mouse;
	int m_MouseWheelDelta;
	int m_KeyCode; // single key code

	void Clear() {
		m_Size = sf::Vector2i(0, 0);
		m_TextEntered = 0;
		m_Mouse = sf::Vector2i(0, 0);
		m_MouseWheelDelta = 0;
		m_KeyCode = -1;
	}
};

struct Binding {
	Binding(const string& l_Name) :
		m_Name(l_Name), m_Details(l_Name), c(0) {

	}

	void BindEvent(EventType l_Type,
		EventInfo l_Info = EventInfo()) {

		m_Events.emplace_back(l_Type, l_Info);
	}

	Events m_Events;
	string m_Name;
	int c; // count of events that are "happening"

	EventDetails m_Details;
};

using Bindings = unordered_map<string, Binding*>;

using CallBackContainer = unordered_map<string,
	function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = unordered_map<StateType, CallBackContainer>;

class EventManager {
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* l_Binding);
	bool RemoveBinding(string l_Name);

	void SetCurrentState(StateType l_State);
	void SetFocus(const bool& l_Focus);

	template<class T>
	bool AddCallback(StateType l_state, const std::string& l_name, 
		void(T::* l_func)(EventDetails*), T* l_instance)
	{
		auto itr = m_CallBacks.emplace(l_state, CallBackContainer()).first;
		auto temp = bind(l_func, l_instance, placeholders::_1);
		return itr->second.emplace(l_name, temp).second;
	}

	bool RemoveCallback(StateType l_state, const std::string& l_name) {
		auto itr = m_CallBacks.find(l_state);

		if (itr == m_CallBacks.end()) { 
			return false; 
		}

		auto itr2 = itr->second.find(l_name);
		if (itr2 == itr->second.end()) { 
			return false; 
		}

		itr->second.erase(l_name);
		return true;
	}

	void HandleEvent(sf::Event& l_Event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* l_Wind = nullptr) {
		return (l_Wind ? sf::Mouse::getPosition(*l_Wind)
			: sf::Mouse::getPosition());
	}

private:
	void LoadBindings();

	Bindings m_Bindings;
	Callbacks m_CallBacks;
	StateType m_CurrentState;
	bool m_HasFocus;
};
#endif
