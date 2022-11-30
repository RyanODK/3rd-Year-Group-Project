#include "EntityManager.h"

EntityManager::EntityManager(SharedContext* l_Context, unsigned int l_MaxEntities) :
	m_Context(l_Context), m_MaxEntities(l_MaxEntities), m_IdCounter(0) {
	
	LoadEnemyTypes("EnemyList.list");
	RegisterEntity<Player>(EntityType::Player);
	//RegisterEntity<Enemy>(EntityType::Enemy);
}

EntityManager::~EntityManager() {
	Purge();
}

int EntityManager::Add(const EntityType& l_Type, const std::string& l_Name) {
	auto itr = m_EntityFactory.find(l_Type);
	if (itr == m_EntityFactory.end()) {
		return -1;
	}
	EntityBase* entity = itr->second();
	entity->m_Id = m_IdCounter;

	if (l_Name != "") {
		entity->m_Name = l_Name;
	}

	m_Entities.emplace(m_IdCounter, entity);

	/*if (l_Type == EntityType::Enemy) {
		auto itr = m_EnemyTypes.find(l_Name);

		if (itr != m_EnemyTypes.end()) {
			Enemy* enemy = (Enemy*)entity;
			enemy->Load(itr->second);
		}
	}*/

	m_IdCounter++;
	return m_IdCounter - 1;
}

EntityBase* EntityManager::Find(const std::string& l_Name) {
	for (auto& itr : m_Entities) {
		if (itr.second->GetName() == l_Name) {
			return itr.second;
		}
	}

	return nullptr;
}

EntityBase* EntityManager::Find(unsigned int l_Id) {
	auto itr = m_Entities.find(l_Id);

	if (itr == m_Entities.end()) {
		return nullptr;
	}

	return itr->second;
}

void EntityManager::Remove(unsigned int l_Id) {
	m_EntitiesToRemove.emplace_back(l_Id);
}

void EntityManager::Update(float l_DeltaTime) {
	for (auto& itr : m_Entities) {
		itr.second->Update(l_DeltaTime);
	}

	EntityCollisionCheck();
	ProcessRemovals();
}

void EntityManager::Draw() {
	sf::RenderWindow* window = m_Context->m_Wind->GetRenderWindow();
	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();

	for (auto& itr : m_Entities) {
		if (!viewSpace.intersects(itr.second->m_AABB)) {
			continue;
		}
		itr.second->Draw(window);
	}
}

void EntityManager::Purge() {
	for (auto& itr : m_Entities) {
		delete itr.second;
	}
	m_Entities.clear();
	m_IdCounter = 0;
}

void EntityManager::ProcessRemovals() {
	while (m_EntitiesToRemove.begin() != m_EntitiesToRemove.end()) {
		unsigned int id = m_EntitiesToRemove.back();
		auto itr = m_Entities.find(id);

		if (itr != m_Entities.end()) {
			std::cout << "Discarding entity: " << itr->second->GetId() << std::endl;
			delete itr->second;
			m_Entities.erase(itr);
		}
		m_EntitiesToRemove.pop_back();
	}
}

void EntityManager::EntityCollisionCheck() {
	if (m_Entities.empty()) {
		return;
	}

	for (auto itr = m_Entities.begin(); std::next(itr) != m_Entities.end(); itr++) {
		for (auto itr2 = std::next(itr); itr2 != m_Entities.end(); itr2++) {
			if (itr->first == itr2->first) {
				continue;
			}

			// Regular AABB Bounding box collision
			if (itr->second->m_AABB.intersects(itr2->second->m_AABB))
			{
				itr->second->OnEntityCollision(itr2->second, false);
				itr2->second->OnEntityCollision(itr->second, false);
			}

			EntityType t1 = itr->second->GetType();
			EntityType t2 = itr2->second->GetType();
			if (t1 == EntityType::Player || t1 == EntityType::Enemy) {
				Character* c1 = (Character*)itr->second;
				if (c1->m_AttackAABB.intersects(itr2->second->m_AABB)) {
					c1->OnEntityCollision(itr2->second, true);
				}
			}

			if (t2 == EntityType::Player || t2 == EntityType::Enemy) {
				Character* c2 = (Character*)itr2->second;

				if (c2->m_AttackAABB.intersects(itr->second->m_AABB)) {
					c2->OnEntityCollision(itr->second, true);
				}
			}
		}
	}
}

void EntityManager::LoadEnemyTypes(const std::string& l_Name) {
	std::ifstream file;
	std::string line;

	file.open(Utils::GetWorkingDirectory() + std::string("Code/") + l_Name);
	if (!file.is_open()) {
		std::cout << "! Failed loading file: " << l_Name << std::endl;
		return;
	}

	while (std::getline(file, line)) {
		if (line[0] == '|') {
			continue;
		}

		std::stringstream keystream(line);
		std::string name;
		std::string charFile;
		keystream >> name >> charFile;
		m_EnemyTypes.emplace(name, charFile);
	}
	file.close();
}