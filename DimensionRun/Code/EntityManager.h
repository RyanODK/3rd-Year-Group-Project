#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include "Player.h"
#include "SharedContext.h"

using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase* (void)>>;
using EnemyTypes = std::unordered_map<std::string, std::string>;

class EntityManager {
public:
	EntityManager(SharedContext* l_Context, unsigned int l_MaxEntities);
	~EntityManager();

	int Add(const EntityType& l_Type, const std::string& l_Name = "");
	EntityBase* Find(unsigned int l_Id);
	EntityBase* Find(const std::string& l_Name);
	void Remove(unsigned int l_Id);

	void Update(float l_DeltaTime);
	void Draw();

	void Purge();

	SharedContext* GetContext();

private:
	template<class T>
	void RegisterEntity(const EntityType& l_Type) {
		m_EntityFactory[l_Type] = [this]() -> EntityBase* {
			return new T(this);
		};
	}

	void ProcessRemovals();
	void LoadEnemyTypes(const std::string& l_Name);
	void EntityCollisionCheck();

	EntityContainer m_Entities;
	EnemyTypes m_EnemyTypes;
	EntityFactory m_EntityFactory;
	SharedContext* m_Context;
	unsigned int m_IdCounter;
	unsigned int m_MaxEntities;

	std::vector<unsigned int> m_EntitiesToRemove;
};
