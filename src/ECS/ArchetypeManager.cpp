#include "Generic/ECS/ArchetypeManager.h"
#include "Generic/Util/Util.h"
#include "Generic/ECS/EntityManager.h"

int Generic::ArchetypeManager::addEntity(int entityTypeId, const VLUI64& entityTypeMask) {
	int entityId = entityIDsAllocator.getName();
	assertNoAbort([&entityTypeId, entityTypeMask]()->bool {return EntityManager::entityTypeExists(entityTypeMask); }, 
        "ArchetypeManager :: addEntity :: entity type not found");
	int entityLocalId = archetypes[entityTypeId].addEntity(entityTypeId, entityTypeMask);
	entityLocations[entityId] = {entityTypeId, entityLocalId };
	return entityId;
}

void Generic::ArchetypeManager::removeEntity(int entityId) {
    assertNoAbort([&entityId]()->bool {return entityLocations.find(entityId) != entityLocations.end(); },
        "ArchetypeManager :: removeEntity :: Entity with ID " + std::to_string(entityId) + " not found");

    const auto& location = entityLocations[entityId];
    int entityTypeId = location.first;
    int entityLocalId = location.second;

    assertNoAbort([&entityTypeId]()->bool {return entityTypeId < Generic::EntityManager::maxEntityTypeCount; },
        "ArchetypeManager :: removeEntity :: entity type ID " + std::to_string(entityTypeId) + "out of bounds,"
        " you may increase maximum entity type count if required.");

    bool lastEntityCopied = archetypes[entityTypeId].removeEntity(entityTypeId, entityLocalId);

    switch (lastEntityCopied)
    {
    case true:
        entityLocations[std::prev(entityLocations.end())->first].second = entityLocalId;
        break;
    }

    entityLocations.erase(entityId);
	entityIDsAllocator.returnName(entityId);
}

void Generic::ArchetypeManager::addArchetypeRecursive(const int& entityTypeId, const VLUI64& entityTypeMask) {
    archetypes.insert({entityTypeId, Archetype()});

    std::function<void(const VLUI64&, int)> f = [&entityTypeId, &f](const VLUI64& entityTypeMask, int componentTypeId) {
        VLUI64 subEntityTypeMask = entityTypeMask;
        subEntityTypeMask.clear(componentTypeId);
        if (subEntityTypeMask.isEmpty())
            return;
        if (EntityManager::entityTypeExists(subEntityTypeMask))
            return;
        int subArchetypeId = EntityManager::addEntityType(subEntityTypeMask);
        archetypes.insert({ subArchetypeId, Archetype() });
        archetypes[subArchetypeId].addLink(GRTTI::typeMask(componentTypeId), &archetypes[entityTypeId]);
        };

    entityTypeMask.iterateBits(f);
}

Component* Generic::ArchetypeManager::getComponent(const int& entityId, const int& componentTypeId)
{
    int entityType = entityLocations[entityId].first;
    return archetypes[entityType].getComponent(entityId, componentTypeId, std::move(entityTypeNames[entityType]));
}

void Generic::ArchetypeManager::addEntityTypeName(const int& entityTypeId, std::string &&name)
{
    entityTypeNames[entityTypeId] = name;
}

void Generic::ArchetypeManager::getArchetypesWithComponents(int _archetype, const VLUI64&& included, const VLUI64& excluded, std::vector<Archetype*>& _archetypes) {
    //static Archetype& archetype = (archetypes[_archetype].linked == true) ? linkArchetype(archetypes[_archetype], included) : archetypes[_archetype];
    
}

//(archetypes[_archetype].linked == true) ? linkArchetype(archetypes[_archetype]) : 

Generic::NameAllocator Generic::ArchetypeManager::typeIDsAllocator = Generic::NameAllocator(Generic::EntityManager::maxEntityTypeCount);
std::unordered_map<int, std::vector<int>> Generic::ArchetypeManager::componentTypeIdsList;
std::unordered_map<int, Generic::Archetype> Generic::ArchetypeManager::archetypes;
Generic::NameAllocator Generic::ArchetypeManager::entityIDsAllocator = Generic::NameAllocator(maxEntityCount);
std::unordered_map<int, std::pair<int, int>> Generic::ArchetypeManager::entityLocations;
std::unordered_map<int, std::string> Generic::ArchetypeManager::entityTypeNames;
