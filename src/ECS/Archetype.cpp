#include "Generic/ECS/Archetype.h"
#include "Generic/ECS/ComponentManager.h"
#include "Generic/ECS/EntityManager.h"

int Generic::Archetype::addEntity(const int &entityTypeId, const VLUI64& entityTypeMask) {
	int entityId = entityIdAllocator.getName();
	assertNoAbort([&entityId]()->bool {return entityId < maxEntityCountPerArchetype; },
		"Archetype :: addEntity :: maximum entity count reached :: you may increase maximum entity count for all archetypes");
	entityTypeMask.iterateBits([&, entityId, entityTypeId, this](const VLUI64& mask, int componentTypeId) {
		entities[componentTypeId][entityId] = ComponentManager::getComponent(entityTypeId, componentTypeId); });
	return entityId;
}

bool Generic::Archetype::removeEntity(const int& entityTypeId, const int &entityLocalId) {
	assertNoAbort([&entityLocalId, this]()->bool {return entityIdAllocator.isReserved(entityLocalId); },
		"Archetype :: removeEntity :: cannot remove entity since it does not belong to this archetype");
	for (auto &componentType : entities)
	{
		bool componentTypeSizeSmallEnough = ComponentManager::componentTypeSizes[componentType.first] < 20;

		switch (componentTypeSizeSmallEnough) {
		case false: //no copy
			entityIdAllocator.returnName(entityLocalId);
			ComponentManager::returnComponent(entityTypeId, componentType.first, componentType.second[entityLocalId]);
			return false;
			break;
		case true: //potential copy
			bool entityIsLast = entityLocalId == entityIdAllocator.lastNameReserved();
			switch (entityIsLast) {
			case true: //no copy
				entityIdAllocator.returnName(entityLocalId);
				ComponentManager::returnComponent(entityTypeId, componentType.first, componentType.second[entityLocalId]);
				return false;
				break;
			case false: //copy component
				entityIdAllocator.returnName(entityIdAllocator.lastNameReserved());
				ComponentManager::returnComponentWithCopy(entityTypeId, componentType.first, componentType.second[entityLocalId]);
				
				return true;
				break;
			}
			return true;
			break;
		}
	}
}

void Generic::Archetype::addLink(const VLUI64& mask, Archetype* archetype) {
	superArchetypes[mask] = archetype;
}


Component* Generic::Archetype::getComponent(const int& entityId, const int& componentTypeId, std::string&& name)
{
	assertNoAbort([this, &componentTypeId]()->bool {return entities.find(componentTypeId) != entities.end(); },
		"Archetype :: getComponent :: no such component type found in archetype " + name);
	return entities[componentTypeId][entityId];
}
