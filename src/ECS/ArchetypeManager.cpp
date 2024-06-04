#include "Generic/ECS/ArchetypeManager.h"
#include "Generic/Util/Util.h"
#include "Generic/ECS/EntityManager.h"

int Generic::ArchetypeManager::addEntity(int entityTypeId) {
	int entityId = entityIDsAllocator.getName();
	assertNoAbort([&entityTypeId]()->bool {return entityTypeId < EntityManager::maxEntityTypeCount; }, "ArchetypeManager :: entity type id out of bounds");
	int entityIndex = archetypes[entityTypeId].addEntity(entityTypeId);
	entityLocations[entityId] = {entityTypeId, entityIndex};
	return entityId;
}

Generic::NameAllocator Generic::ArchetypeManager::typeIDsAllocator = Generic::NameAllocator(Generic::EntityManager::maxEntityTypeCount);
std::unordered_map<int, std::vector<int>> Generic::ArchetypeManager::componentTypeIdsList;
Generic::Archetype Generic::ArchetypeManager::archetypes[Generic::EntityManager::maxEntityTypeCount];
Generic::NameAllocator Generic::ArchetypeManager::entityIDsAllocator = Generic::NameAllocator(maxEntityCount);
std::pair<int, int> Generic::ArchetypeManager::entityLocations[maxEntityCount];