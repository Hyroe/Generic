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

bool Generic::ECS::ArchetypeManager::removeEntity(int entityId) {
    if (entityLocations.find(entityId) == entityLocations.end()) {
        Core::Logger::logError("Entity with ID " + std::to_string(entityId) + " not found");
        return false;
    }

    const auto& location = entityLocations[entityId];
    int entityTypeId = location.first;
    int entityLocalId = location.second;

    if (archetypes.find(entityTypeId) != archetypes.end()) {
        archetypes[entityTypeId].removeEntity(entityLocalId);
    } else {
        Core::Logger::logError("Archetype for entity type ID " + std::to_string(entityTypeId) + " not found");
    }

    entityLocations.erase(entityId);
	entityIDsAllocator.returnName(entityId);
	return true;
}

Generic::NameAllocator Generic::ArchetypeManager::typeIDsAllocator = Generic::NameAllocator(Generic::EntityManager::maxEntityTypeCount);
std::unordered_map<int, std::vector<int>> Generic::ArchetypeManager::componentTypeIdsList;
Generic::Archetype Generic::ArchetypeManager::archetypes[Generic::EntityManager::maxEntityTypeCount];
Generic::NameAllocator Generic::ArchetypeManager::entityIDsAllocator = Generic::NameAllocator(maxEntityCount);
std::pair<int, int> Generic::ArchetypeManager::entityLocations[maxEntityCount];
