#include "Generic/ECS/Archetype.h"
#include "Generic/ECS/ComponentManager.h"

int Generic::ECS::Archetype::addEntity(std::vector<int> componentTypeIdArray) {
	int entityId = entityIdAllocator.getName();
	for (int componentTypeId : componentTypeIdArray)
	{
		entities[componentTypeId][entityId] = ComponentManager::getComponent(id, componentTypeId);
	}
	return entityId;
}
