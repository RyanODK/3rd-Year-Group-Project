#pragma once
#include <queue>

using EventID = unsigned int;

class EventQueue {
public:
	void AddEvent(const EventID& l_event) { 
		m_Queue.push(l_event); 
	}

	bool ProcessEvents(EventID& l_id) {
		if (m_Queue.empty()) { 
			return false; 
		}

		l_id = m_Queue.front();
		m_Queue.pop();
		return true;
	}

	void Clear() { 
		while (!m_Queue.empty()) { 
			m_Queue.pop(); 
		} 
	}
private:
	std::queue<EventID> m_Queue;
};
