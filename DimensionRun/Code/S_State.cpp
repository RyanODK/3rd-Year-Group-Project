#include "S_State.h"
#include "SystemManager.h"

S_State::S_State(SystemManager* l_systemMgr)
	: S_Base(System::State, l_systemMgr)
{
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::State);
	m_RequiredComponents.push_back(req);

	m_SystemManager->GetMessageHandler()->Subscribe(EntityMessage::Move, this);
	m_SystemManager->GetMessageHandler()->Subscribe(EntityMessage::Switch_State, this);
}

S_State::~S_State() {}

void S_State::Update(float l_dT) {
	EntityManager* entities = m_SystemManager->GetEntityManager();
	for (auto& entity : m_Entities) {
		C_State* state = entities->GetComponent<C_State>(entity, Component::State);
		if (state->GetState() == EntityState::Running) {
			Message msg((MessageType)EntityMessage::Is_Moving);
			msg.m_receiver = entity;
			m_SystemManager->GetMessageHandler()->Dispatch(msg);
		}
	}
}

void S_State::HandleEvent(const EntityId& l_entity,
	const EntityEvent& l_event)
{
	switch (l_event) {
	case EntityEvent::Became_Idle:
		ChangeState(l_entity, EntityState::Running, false);
		break;
	}
}

void S_State::Notify(const Message& l_message) {
	if (!HasEntity(l_message.m_receiver)) { 
		return; 
	}

	EntityMessage m = (EntityMessage)l_message.m_type;
	switch (m) {
	case EntityMessage::Move:
	{
		C_State* state = m_SystemManager->GetEntityManager()->
			GetComponent<C_State>(l_message.m_receiver, Component::State);

		if (state->GetState() == EntityState::Dying) { return; }
		EntityEvent e;
		if (l_message.m_int == (int)Direction::Up) {
			e = EntityEvent::Moving_Up;
		}
		else if (l_message.m_int == (int)Direction::Down) {
			e = EntityEvent::Moving_Down;
		}
		else if (l_message.m_int == (int)Direction::Left) {
			e = EntityEvent::Moving_Left;
		}
		else if (l_message.m_int == (int)Direction::Right) {
			e = EntityEvent::Moving_Right;
		}

		m_SystemManager->AddEvent(l_message.m_receiver, (EventID)e);
		ChangeState(l_message.m_receiver, EntityState::Running, false);
	}
	break;
	case EntityMessage::Switch_State:
		ChangeState(l_message.m_receiver,
			(EntityState)l_message.m_int, false);
		break;
	}
}

void S_State::ChangeState(const EntityId& l_entity,
	const EntityState& l_state, bool l_force)
{
	EntityManager* entities = m_SystemManager->GetEntityManager();
	C_State* state = entities->GetComponent<C_State>(l_entity, Component::State);
	if (!l_force && state->GetState() == EntityState::Dying) { return; }
	state->SetState(l_state);
	Message msg((MessageType)EntityMessage::State_Changed);
	msg.m_receiver = l_entity;
	msg.m_int = (int)l_state;
	m_SystemManager->GetMessageHandler()->Dispatch(msg);
}