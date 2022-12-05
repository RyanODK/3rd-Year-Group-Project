#pragma once
#include "Communicator.h"
#include "EntityMessage.h"
#include <unordered_map>

using Subscriptions = std::unordered_map<EntityMessage, Communicator>;

class MessageHandler {
public:
	bool Subscribe(const EntityMessage& l_type, Observer* l_observer)
	{
		return m_communicators[l_type].AddObserver(l_observer);
	}

	bool Unsubscribe(const EntityMessage& l_type, Observer* l_observer)
	{
		return m_communicators[l_type].RemoveObserver(l_observer);
	}

	void Dispatch(const Message& l_msg) {
		auto itr = m_communicators.find((EntityMessage)l_msg.m_type);
		if (itr == m_communicators.end()) { 
			return;
		}
		itr->second.Broadcast(l_msg);
	}
private:
	Subscriptions m_communicators;
};