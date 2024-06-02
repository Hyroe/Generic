#include "Generic/ECS/EntityManager.h"

int Generic::ECS::EntityManager::addEntity(int entityTypeId) {
	return ArchetypeManager::addEntity(entityTypeId);
}

int Generic::ECS::EntityManager::entityTypeIDCount = 0;
std::unordered_map<int, Generic::Util::VLUI64> Generic::ECS::EntityManager::entityTypeMasks;