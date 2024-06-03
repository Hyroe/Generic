#include "Generic/ECS/ArchetypeManager.h"
#include "Generic/Core/Logger.h"
#include "Generic/ECS/EntityManager.h"

int Generic::ECS::ArchetypeManager::addEntity(int entityTypeId) {
	if (componentTypeIdsList.find(entityTypeId) == componentTypeIdsList.end())
	{
		Core::Logger::logError("entity type id " + std::to_string(entityTypeId) + " not found");
		return -1;
	}
	int entityId = entityIDsAllocator.getName();
	int entityLocalId = archetypes[entityTypeId].addEntity(componentTypeIdsList[entityTypeId]);
	entityLocations[entityId] = std::make_pair(entityTypeId, entityLocalId);
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


Generic::Util::NameAllocator Generic::ECS::ArchetypeManager::typeIDsAllocator = Generic::Util::NameAllocator(20);
std::unordered_map<int, std::vector<int>> Generic::ECS::ArchetypeManager::componentTypeIdsList;
std::unordered_map<int, Generic::ECS::Archetype> Generic::ECS::ArchetypeManager::archetypes;
Generic::Util::NameAllocator Generic::ECS::ArchetypeManager::entityIDsAllocator = Generic::Util::NameAllocator(Generic::ECS::EntityManager::maxEntityTypeCount);
std::unordered_map<int, std::pair<int, int>> Generic::ECS::ArchetypeManager::entityLocations;