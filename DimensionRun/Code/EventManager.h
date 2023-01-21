#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "GUI_Event.h"

// enumeration table for all possible events
// last row (keyboard) is terminated to prevent identifer clashes
// this makes sure anything added past keyboard is higher than the absolute maximum Event::EventType
// this is because all enums are keywords pointing to integer values
enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	JoystickButtonDown = sf::Event::JoystickButtonPressed,
	JoystickButtonUp = sf::Event::JoystickButtonReleased,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick,
	GUI_Click, GUI_Release, GUI_Hover, GUI_Leave
};

// this struct stores these events for each binding in keys.cfg
// union leaves room for expansion later 
struct EventInfo {
	EventInfo() {
		m_Code = 0;
	}
	EventInfo(int l_Event) {
		m_Code = l_Event;
	}
	EventInfo(const GUI_Event& l_guiEvent) { 
		m_Gui = l_guiEvent; 
	}
	union {
		int m_Code;
		GUI_Event m_Gui;
	};
};

// this data type holds the event information
using Events = std::vector<std::pair<EventType, EventInfo>>;

// this struct shares the event information with the EventManager code to make it all work together
struct EventDetails {
	EventDetails(const std::string& l_BindName) :
		m_Name(l_BindName) {

		Clear();
	}
	std::string m_Name;

	sf::Vector2i m_Size;
	sf::Uint32 m_TextEntered;
	sf::Vector2i m_Mouse;
	int m_MouseWheelDelta;
	int m_KeyCode; // single key code
	int m_ButtonCode;

	std::string m_guiInterface;
	std::string m_guiElement;
	GUI_EventType m_guiEvent;

	void Clear() {
		m_Size = sf::Vector2i(0, 0);
		m_TextEntered = 0;
		m_Mouse = sf::Vector2i(0, 0);
		m_MouseWheelDelta = 0;
		m_KeyCode = -1;
		m_ButtonCode = -1;
		m_guiInterface = "";
		m_guiElement = "";
		m_guiEvent = GUI_EventType::None;
	}
};

// this struct binds the events and sets up initialiser list to set up class data members
struct Binding {
	Binding(const std::string& l_Name) :
		m_Name(l_Name), m_Details(l_Name), c(0) {

	}

	~Binding() {
		// GUI portion.
		for (auto itr = m_Events.begin();
			itr != m_Events.end(); ++itr)
		{
			if (itr->first == EventType::GUI_Click || itr->first == EventType::GUI_Release ||
				itr->first == EventType::GUI_Hover || itr->first == EventType::GUI_Leave)
			{
				delete [] itr->second.m_Gui.m_interface;
				delete [] itr->second.m_Gui.m_element;
			}
		}
	}

	void BindEvent(EventType l_Type,
		EventInfo l_Info = EventInfo()) {

		m_Events.emplace_back(l_Type, l_Info);
	}

	Events m_Events;
	std::string m_Name;
	int c; // count of events that are "happening"

	EventDetails m_Details;
};

// this stores the bindings in an unordered_map
// unordered_map makes sure there is only one binding per action
using Bindings = std::unordered_map<std::string, Binding*>;

// we use callbacks to link a piece of code to another piece of code
// this allows us to execute a binding from keys.cfg when we want
// for example our sprite has a method Jump(), which is the callback
// we will bind this method to the "Jump" action name in keys.cfg 
using CallBackContainer = std::unordered_map<std::string,
	std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallBackContainer>;

class EventManager {
public:
	EventManager();
	~EventManager(); // as binding are stored on the heap
					//  these dynamic memories need to be deallocated

	/*
		AddBinding will take in a pointer to a binding
		it will then check if the binder container already contains this binding with the same name
		if it does then it returns false 

		RemoveBinding will iterate over the container for a match 
		if it finds the match then it frees memory by deleting the second element of key-value pair
		this is where the dynamic memory is allocated for the binding object
		then it erases the entry from the container altogether and returns true for success
	*/
	bool AddBinding(Binding* l_Binding); 
	bool RemoveBinding(std::string l_Name);

	void SetCurrentState(StateType l_State);
	void SetFocus(bool l_Focus);

	/*
		you can think of template as a placeholder class
		AddCallBack() is what will bind a method to the action name in keys.cfg
	*/
	template<class T>
	bool AddCallback(StateType l_state, const std::string& l_name, 
		void(T::*l_func)(EventDetails*), T* l_instance)
	{
		auto itr = m_CallBacks.emplace(l_state, CallBackContainer()).first;
		auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
		return itr->second.emplace(l_name, temp).second;
	}

	/*
		This will remove the link between a method and the action name in keys.cfg
	*/
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

	/*
		HandleEvent iterates through all bindings and through each event in the binding
		if there is a match, then it checks whether its a mouse or keyboard event
		then it checks the keyboard and mouse key codes


		Update iterates over the bindings and their events again like before
		incrementing the c data member will register a match

		it then checks if the number of events in the event container 
		matches the number of events that are on
		if thats the case then it locates the callback container and implements the callback
		then it will reset c back to 0 for the next iteration

		Update also has support for a Joystick which most likely will be added in the future 
	*/
	void HandleEvent(sf::Event& l_Event);
	void HandleEvent(GUI_Event& l_event);
	void Update();

	/*
		This will return the mouse cursor position to the console
	*/
	sf::Vector2i GetMousePos(sf::RenderWindow* l_Wind = nullptr) {
		//std::cout << sf::Mouse::getPosition().x << sf::Mouse::getPosition().y << std::endl;
		return (l_Wind ? sf::Mouse::getPosition(*l_Wind)
			: sf::Mouse::getPosition());
	}

	sf::Vector2i GetJoystickPos(sf::RenderWindow* l_Wind = nullptr) {
		std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::X) <<
			sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
		sf::Mouse::setPosition(sf::Vector2i(
			sf::Joystick::getAxisPosition(0, sf::Joystick::X),
			sf::Joystick::getAxisPosition(0, sf::Joystick::Y)));
		/*return sf::Vector2i(sf::Joystick::getAxisPosition(0, sf::Joystick::X), 
			sf::Joystick::getAxisPosition(0, sf::Joystick::Y));*/

		return (l_Wind ? sf::Mouse::getPosition(*l_Wind)
			: sf::Mouse::getPosition());
	}

private:
	void LoadBindings(); // this will load the bindings made in keys.cfg

	Bindings m_Bindings;
	Callbacks m_CallBacks;
	StateType m_CurrentState;
	bool m_HasFocus;
};
