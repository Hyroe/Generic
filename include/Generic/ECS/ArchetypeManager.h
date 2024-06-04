#ifndef ARCHETYPE_MANAGER_H
#define ARCHETYPE_MANAGER_H

#include <unordered_map>
#include "Generic/Util/VLUI64.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Archetype.h"
#include <vector>

namespace Generic {
		class ArchetypeManager
		{
		public:
			static int addEntity(int entityTypeId);
			static bool removeEntity(int entityId);

    private:
      static constexpr int maxEntityCount = 20;
      static Archetype archetypes[];
      static std::unordered_map<int, std::vector<int>> componentTypeIdsList;
      static NameAllocator typeIDsAllocator;
      static NameAllocator entityIDsAllocator;
      static std::pair<int, int> entityLocations[];
	};
}

#endif 