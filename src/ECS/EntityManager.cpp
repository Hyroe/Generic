#include "Generic/ECS/EntityManager.h"

int Generic::EntityManager::addEntity(int entityTypeId) {
	return ArchetypeManager::addEntity(entityTypeId, entityTypeMasks[entityTypeId]);
}

void Generic::EntityManager::removeEntity(int entityId)
{
	ArchetypeManager::removeEntity(entityId);
}

int Generic::EntityManager::entityTypeIDCount = 0;
std::unordered_map<int, Generic::VLUI64> Generic::EntityManager::entityTypeMasks;
std::map<Generic::VLUI64, int> Generic::EntityManager::entityTypeIDs;
std::unordered_map<int, std::vector<int>> Generic::EntityManager::entityTypeLists;