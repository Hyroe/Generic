#ifndef ARCHETYPE_MANAGER_H
#define ARCHETYPE_MANAGER_H

#include <unordered_map>
#include "Generic/Util/VLUI64.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Archetype.h"
#include <vector>
#include <string>

namespace Generic {
	class ArchetypeManager
	{
	public:
		static int addEntity(int entityTypeId, const VLUI64& entityTypeMask);
		static void removeEntity(int entityId);
        static void getArchetypesWithComponents(int archetype, const VLUI64&& included, const VLUI64& excluded,  std::vector<Archetype*>& archetypes);
        static void addArchetypeRecursive(const int& entityTypeId, const VLUI64& entityTypeMask);
        static Component* getComponent(const int &entityId, const int& componentTypeId);
        static void addEntityTypeName(const int& entityTypeId, std::string &&name);

    private:

        static constexpr int maxEntityCount = 20;
        static std::unordered_map<int, Archetype> archetypes;
        static std::unordered_map<int, std::vector<int>> componentTypeIdsList;
        static NameAllocator typeIDsAllocator;
        static NameAllocator entityIDsAllocator;
        static std::unordered_map<int, std::pair<int, int>> entityLocations;
        static std::unordered_map<int, std::string> entityTypeNames;
	};
}

#endif 