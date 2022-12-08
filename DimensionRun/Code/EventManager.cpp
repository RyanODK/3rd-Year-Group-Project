#include "EventManager.h"

EventManager::EventManager() : 
	m_CurrentState(StateType(0)), m_HasFocus(true) {
	LoadBindings();
}

EventManager::~EventManager() {
	for (auto& itr : m_Bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* l_Binding) {
	if (m_Bindings.find(l_Binding->m_Name) != m_Bindings.end()) {
		return false;
	}

	return m_Bindings.emplace(l_Binding->m_Name,
		l_Binding).second;
}

bool EventManager::RemoveBinding(std::string l_Name) {
	auto itr = m_Bindings.find(l_Name);
	if (itr == m_Bindings.end()) {
		return false;
	}

	delete itr->second;
	m_Bindings.erase(itr);
	return true;
}

void EventManager::SetCurrentState(StateType l_state) {
	m_CurrentState = l_state;
}

void EventManager::SetFocus(bool l_focus) { 
	m_HasFocus = l_focus; 
}

void EventManager::HandleEvent(sf::Event& l_Event) {
	// Handle SFML events
	for (auto& b_itr : m_Bindings) {
		Binding* bind = b_itr.second;

		for (auto& e_itr : bind->m_Events) {
			EventType sfmlEvent = (EventType)l_Event.type;

			if (e_itr.first == EventType::GUI_Click || e_itr.first == EventType::GUI_Release ||
				e_itr.first == EventType::GUI_Hover || e_itr.first == EventType::GUI_Leave)
			{
				continue;
			}

			if (e_itr.first != sfmlEvent) {
				continue;
			}

			if (sfmlEvent == EventType::KeyDown ||
				sfmlEvent == EventType::KeyUp) {

				if (e_itr.second.m_Code == l_Event.key.code) {
					// matching event/keystroke
					// increase count
					if (bind->m_Details.m_KeyCode != -1) {
						bind->m_Details.m_KeyCode = e_itr.second.m_Code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown ||
				sfmlEvent == EventType::MButtonUp) {

				if (e_itr.second.m_Code == l_Event.mouseButton.button) {
					// matching event/keystroke
					// increase count
					bind->m_Details.m_Mouse.x = l_Event.mouseButton.x;
					bind->m_Details.m_Mouse.y = l_Event.mouseButton.y;

					if (bind->m_Details.m_KeyCode != -1) {
						bind->m_Details.m_KeyCode = e_itr.second.m_Code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// no need for additional checking
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_Details.m_MouseWheelDelta = l_Event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->m_Details.m_Size.x = l_Event.size.width;
					bind->m_Details.m_Size.y = l_Event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_Details.m_TextEntered = l_Event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::HandleEvent(GUI_Event& l_event) {
	for (auto& b_itr : m_Bindings) {
		Binding* bind = b_itr.second;
		for (auto& e_itr : bind->m_Events)
		{
			if (e_itr.first != EventType::GUI_Click && e_itr.first != EventType::GUI_Release &&
				e_itr.first != EventType::GUI_Hover && e_itr.first != EventType::GUI_Leave)
			{
				continue;
			}
			if ((e_itr.first == EventType::GUI_Click && l_event.m_type != GUI_EventType::Click) ||
				(e_itr.first == EventType::GUI_Release && l_event.m_type != GUI_EventType::Release) ||
				(e_itr.first == EventType::GUI_Hover && l_event.m_type != GUI_EventType::Hover) ||
				(e_itr.first == EventType::GUI_Leave && l_event.m_type != GUI_EventType::Leave))
			{
				continue;
			}
			// REPLACED WITH STRCMP!
			if (strcmp(e_itr.second.m_Gui.m_interface, l_event.m_interface) ||
				strcmp(e_itr.second.m_Gui.m_element, l_event.m_element))
			{
				continue;
			}
			bind->m_Details.m_guiInterface = l_event.m_interface;
			bind->m_Details.m_guiElement = l_event.m_element;
			++(bind->c);
		}
	}
}

void EventManager::Update() {
	if (!m_HasFocus) {
		return;
	}

	for (auto& b_itr : m_Bindings) {
		Binding* bind = b_itr.second;

		for (auto& e_itr : bind->m_Events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(
					sf::Keyboard::Key(e_itr.second.m_Code))) {
					if (bind->m_Details.m_KeyCode != -1) {
						bind->m_Details.m_KeyCode = e_itr.second.m_Code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(
					sf::Mouse::Button(e_itr.second.m_Code)))
				{
					if (bind->m_Details.m_KeyCode != -1) {
						bind->m_Details.m_KeyCode = e_itr.second.m_Code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// Up for expansion.
				break;
			}
		}

		if (bind->m_Events.size() == bind->c) {
			auto stateCallbacks = m_CallBacks.find(m_CurrentState);
			auto otherCallbacks = m_CallBacks.find(StateType(0));

			if (stateCallbacks != m_CallBacks.end()) {
				auto callItr = stateCallbacks->second.find(bind->m_Name);
				if (callItr != stateCallbacks->second.end()) {
					// Pass in information about events.
					callItr->second(&bind->m_Details);
				}
			}

			if (otherCallbacks != m_CallBacks.end()) {
				auto callItr = otherCallbacks->second.find(bind->m_Name);
				if (callItr != otherCallbacks->second.end()) {
					// Pass in information about events.
					callItr->second(&bind->m_Details);
				}
			}
		}
		bind->c = 0;
		bind->m_Details.Clear();
	}
}

void EventManager::LoadBindings() {
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("Code/Resources/keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "! Failed loading keys.cfg." << std::endl;
		return;
	}
	std::string line;
	while (getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			
			if (keystream.fail()) {
				std::cout << "Key failed: " << keyval << std::endl;
				keystream.clear();
				break;
			}

			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) {
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(
				stoi(keyval.substr(start, end - start)));
			
			EventInfo eventInfo;

			if (type == EventType::GUI_Click || type == EventType::GUI_Release ||
				type == EventType::GUI_Hover || type == EventType::GUI_Leave)
			{
				start = end + delimiter.length();
				end = keyval.find(delimiter, start);
				std::string window = keyval.substr(start, end - start);
				std::string element;
				if (end != std::string::npos) {
					start = end + delimiter.length();
					end = keyval.length();
					element = keyval.substr(start, end);
				}
				char* w = new char[window.length() + 1]; // +1 for \0
				char* e = new char[element.length() + 1];

				strcpy_s(w, window.size() + 1, window.c_str());
				strcpy_s(e, element.size() + 1, element.c_str());

				eventInfo.m_Gui.m_interface = w;
				eventInfo.m_Gui.m_element = e;
			}
			else {
				int code = stoi(keyval.substr(end + delimiter.length(),
					keyval.find(delimiter, end + delimiter.length())));
				eventInfo.m_Code = code;
			}

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}