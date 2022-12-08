#include "EntityManager.h"
#include "SystemManager.h"

EntityManager::EntityManager(SystemManager* l_sysMgr,
	TextureManager* l_textureMgr) : m_IDCounter(0),
	m_Systems(l_sysMgr), m_TextureManager(l_textureMgr)
{
	AddComponentType<C_Position>(Component::Position);
	AddComponentType<C_SpriteSheet>(Component::SpriteSheet);
	AddComponentType<C_State>(Component::State);
	AddComponentType<C_Movable>(Component::Movable);
	AddComponentType<C_Controller>(Component::Controller);
	AddComponentType<C_Collidable>(Component::Collidable);
	AddComponentType<C_SoundEmitter>(Component::SoundEmitter);
	AddComponentType<C_SoundListener>(Component::SoundListener);
}

EntityManager::~EntityManager() { 
	Purge(); 
}

int EntityManager::AddEntity(const Bitmask& l_mask) {
	unsigned int entity = m_IDCounter;
	if (!m_Entities.emplace(entity, EntityData(0, ComponentContainer())).second)
	{
		return -1;
	}
	++m_IDCounter;
	
	for (unsigned int i = 0; i < N_COMPONENT_TYPES; ++i) {
		if (l_mask.GetBit(i)) { 
			AddComponent(entity, (Component)i); 
		}
	}
	// Notifying the system manager of a modified entity.
	m_Systems->EntityModified(entity, l_mask);
	m_Systems->AddEvent(entity, (EventID)EntityEvent::Spawned);
	return entity;
}

int EntityManager::AddEntity(const std::string& l_entityFile) {
	int EntityId = -1;

	std::ifstream file;
	file.open("Code/Resources/media/Entities/" + l_entityFile + ".entity");
	if (!file.is_open()) {
		std::cout << "! Failed to load entity: " << l_entityFile << std::endl;
		return -1;
	}
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') { 
			continue; 
		}

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name") {

		}
		else if (type == "Attributes") {
			if (EntityId != -1) { 
				continue; 
			}

			Bitset set = 0;
			Bitmask mask;
			keystream >> set;
			mask.SetMask(set);
			EntityId = AddEntity(mask);
			if (EntityId == -1) { 
				return -1; 
			} 
		}
		else if (type == "Component") {
			if (EntityId == -1) { 
				continue; 
			}

			unsigned int c_id = 0;
			keystream >> c_id;
			C_Base* component = GetComponent<C_Base>(EntityId, (Component)c_id);
			if (!component) { 
				continue; 
			}

			keystream >> *component;

			if (component->GetType() == Component::Position) {
				std::cout << "this is position component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::SpriteSheet) {
				C_SpriteSheet* sheet = (C_SpriteSheet*)component;
				sheet->Create(m_TextureManager);
				std::cout << "this is spritesheet component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::State) {
				std::cout << "this is state component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::Movable) {
				std::cout << "this is movable component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::Controller) {
				std::cout << "this is controller component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::Collidable) {
				std::cout << "this is Collidable component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::SoundEmitter) {
				std::cout << "this is SoundEmitter component with: " << c_id << std::endl;
			}

			if (component->GetType() == Component::SoundListener) {
				std::cout << "this is SoundListener component with: " << c_id << std::endl;
			}
		}
	}
	file.close();
	return EntityId;
}

bool EntityManager::RemoveEntity(const EntityId& l_id) {
	auto itr = m_Entities.find(l_id);
	if (itr == m_Entities.end()) { 
		return false; 
	}

	// Removing all components.
	while (itr->second.second.begin() != itr->second.second.end()) {
		delete itr->second.second.back();
		itr->second.second.pop_back();
	}
	m_Entities.erase(itr);
	m_Systems->RemoveEntity(l_id);
	return true;
}

bool EntityManager::AddComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_Entities.find(l_entity);
	if (itr == m_Entities.end()) { 
		return false; 
	}

	if (itr->second.first.GetBit((unsigned int)l_component)) { 
		return false; 
	}

	// Component doesn't exist.
	auto itr2 = m_CFactory.find(l_component);
	if (itr2 == m_CFactory.end()) { 
		return false; 
	}

	// Component type does exist.
	C_Base* component = itr2->second();
	itr->second.second.emplace_back(component);
	itr->second.first.TurnOnBit((unsigned int)l_component);
	// Notifying the system manager of a modified entity.
	m_Systems->EntityModified(l_entity, itr->second.first);
	return true;
}

bool EntityManager::RemoveComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_Entities.find(l_entity);
	if (itr == m_Entities.end()) { 
		return false; 
	}

	// Found the entity.
	if (!itr->second.first.GetBit((unsigned int)l_component)) { 
		return false; 
	}

	// Component exists.
	auto& container = itr->second.second;
	auto component = std::find_if(container.begin(), container.end(),
		[&l_component](C_Base* c) { 
			return c->GetType() == l_component; 
		});

	if (component == container.end()) { 
		return false; 
	}

	delete (*component);
	container.erase(component);
	itr->second.first.ClearBit((unsigned int)l_component);

	m_Systems->EntityModified(l_entity, itr->second.first);
	return true;
}

bool EntityManager::HasComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_Entities.find(l_entity);
	if (itr == m_Entities.end()) { 
		return false; 
	}

	return itr->second.first.GetBit((unsigned int)l_component);
}

void EntityManager::Purge() {
	m_Systems->PurgeEntities();

	for (auto& entity : m_Entities) {
		for (auto &component : entity.second.second) {
			delete component;
		}
		entity.second.second.clear();
		entity.second.first.Clear();
	}
	m_Entities.clear();
	m_IDCounter = 0;
}