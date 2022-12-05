#include "S_Base.h"
#include "SystemManager.h"

S_Base::S_Base(const System& l_id, SystemManager* l_systemMgr)
	: m_ID(l_id), m_SystemManager(l_systemMgr) {}

S_Base::~S_Base() { Purge(); }

bool S_Base::AddEntity(const EntityId& l_entity) {
	if (HasEntity(l_entity)) { 
		return false; 
	}

	m_Entities.emplace_back(l_entity);
	return true;
}

bool S_Base::HasEntity(const EntityId& l_entity) {
	return std::find(m_Entities.begin(),
		m_Entities.end(), l_entity) != m_Entities.end();
}

bool S_Base::RemoveEntity(const EntityId& l_entity) {
	auto entity = std::find_if(m_Entities.begin(), m_Entities.end(),
		[&l_entity](EntityId& id) { 
			return id == l_entity; 
		});

	if (entity == m_Entities.end()) { 
		return false; 
	}

	m_Entities.erase(entity);
	return true;
}

System S_Base::GetId() { 
	return m_ID; 
}

bool S_Base::FitsRequirements(const Bitmask& l_bits) {
	return std::find_if(m_RequiredComponents.begin(), m_RequiredComponents.end(),
		[&l_bits](Bitmask& b) { 
			return b.Matches(l_bits, b.GetMask()); }) != m_RequiredComponents.end();
}

void S_Base::Purge() { 
	m_Entities.clear(); 
}