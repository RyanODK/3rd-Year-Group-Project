#include "SystemManager.h"
#include "EntityManager.h"

SystemManager::SystemManager() : m_EntityManager(nullptr) {
	m_Systems[System::State] = new S_State(this);
	m_Systems[System::Control] = new S_Control(this);
	m_Systems[System::Movement] = new S_Movement(this);
	m_Systems[System::Collision] = new S_Collision(this);
	m_Systems[System::SheetAnimation] = new S_SheetAnimation(this);
	m_Systems[System::Renderer] = new S_Renderer(this);
	m_Systems[System::Sound] = new S_Sound(this);
}

SystemManager::~SystemManager() {
	PurgeSystems();
}

void SystemManager::SetEntityManager(EntityManager* l_entityMgr) {
	if (!m_EntityManager) { 
		m_EntityManager = l_entityMgr; 
	}
}

EntityManager* SystemManager::GetEntityManager() {
	return m_EntityManager;
}

MessageHandler* SystemManager::GetMessageHandler() {
	return &m_Messages;
}

void SystemManager::AddEvent(const EntityId& l_entity,
	const EventID& l_event)
{
	m_Events[l_entity].AddEvent(l_event);
}

void SystemManager::Update(float l_dT) {
	for (auto& itr : m_Systems) {
		itr.second->Update(l_dT);
	}
	HandleEvents();
}

void SystemManager::HandleEvents() {
	for (auto& event : m_Events) {
		EventID id = 0;
		while (event.second.ProcessEvents(id)) {
			for (auto& system : m_Systems)
			{
				if (system.second->HasEntity(event.first)) {
					system.second->HandleEvent(event.first, (EntityEvent)id);
				}
			}
		}
	}
}

void SystemManager::Draw(Window* l_wind, unsigned int l_elevation)
{
	auto itr = m_Systems.find(System::Renderer);
	if (itr == m_Systems.end()) { 
		return; 
	}

	S_Renderer* system = (S_Renderer*)itr->second;
	system->Render(l_wind, l_elevation);
}

void SystemManager::EntityModified(const EntityId& l_entity, const Bitmask& l_bits)
{
	for (auto &s_itr : m_Systems) {
		S_Base* system = s_itr.second;
		if (system->FitsRequirements(l_bits)) {
			if (!system->HasEntity(l_entity)) {
				system->AddEntity(l_entity);
			}
		}
		else {
			if (system->HasEntity(l_entity)) {
				system->RemoveEntity(l_entity);
			}
		}
	}
}

void SystemManager::RemoveEntity(const EntityId& l_entity) {
	for (auto &system : m_Systems) {
		system.second->RemoveEntity(l_entity);
	}
}

void SystemManager::PurgeEntities() {
	for (auto &system : m_Systems) {
		system.second->Purge();
	}
}

void SystemManager::PurgeSystems() {
	for (auto &system : m_Systems) {
		delete system.second;
	}
	m_Systems.clear();
}