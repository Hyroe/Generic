#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Generic/Util/VLUI64.h"
#include "Generic/Util/RTTI.h"
#include "Generic/ECS/ArchetypeManager.h"
#include "Generic/Core/Logger.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Util/Util.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <string>

namespace Generic{

	using ComponentTypeId = int;
	using EntityTypeId = int;

	class EntityManager
	{
	public:
		template <typename T, typename ...Types>
		static int addEntityType() {
			return addEntityType(getEntityTypeMask<T, Types...>());
		}

		static int addEntityType(const VLUI64& entityTypeMask) {
			if (!entityTypeExists(entityTypeMask))
			{
				entityTypeMasks[entityTypeIDCount] = entityTypeMask;
				int entityTypeId = entityTypeIDs[entityTypeMask] = entityTypeIDCount;
				entityTypeMask.iterateBits([](const VLUI64& entityTypeMask, int componentTypeId) {
					entityTypeLists[componentTypeId].push_back(entityTypeIDCount); });
				ArchetypeManager::addArchetypeRecursive(entityTypeIDCount++, entityTypeMask);
				return entityTypeId;
			}
			return entityTypeIDs[entityTypeMask];
		}

		static void setEntityTypeName(const int& entityTypeId, std::string&& name) {
			ArchetypeManager::addEntityTypeName(entityTypeId, std::move(name));
		}

		template <typename T, typename ...Types>
		static int addEntity() {
			const VLUI64& entityTypeMask = getEntityTypeMask<T, Types...>();
			assertNoAbort([&entityTypeMask]()->bool {return entityTypeExists(entityTypeMask); },
				"EntityManager :: addEntity :: entityType " + ((GRTTI::typeName<Types>() + " ") + ... + GRTTI::typeName<T>()) + " not found");
			int entityTypeId = entityTypeIDs[entityTypeMask];
			return addEntity(entityTypeId);
		}

		static int addEntity(int entityTypeId);
		static void removeEntity(int entityId);

		template <typename T>
		static T* getComponent(int &entityId) {
			return (T*)ArchetypeManager::getComponent(entityId, GRTTI::typeId<T>());
		}

		static bool entityTypeExists(const VLUI64& mask) {
			return entityTypeIDs.find(mask) != entityTypeIDs.end();
		}


		static void getArchetypesWithComponents(int included, int excluded, std::vector<Archetype*> &archetypes) {
			//ArchetypeManager::
		}

		//end

		static std::unordered_map<ComponentTypeId, std::vector<EntityTypeId>> entityTypeLists;
		static const int maxEntityTypeCount = 40;
		static int entityTypeIDCount;

	private:
		template <typename T, typename ...Types>
		static VLUI64& getEntityTypeMask() {
			static VLUI64 entityTypeMask = (GRTTI::typeMask<Types>() | ... | GRTTI::typeMask<T>());
			return entityTypeMask;
		}

		//friend void ArchetypeManager::addArchetypeRecursive(const int& entityTypeId, const VLUI64& entityTypeMask);

		static std::map<VLUI64, int> entityTypeIDs;
		static std::unordered_map<int, VLUI64> entityTypeMasks;
	};
}

#endif 