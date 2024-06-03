#ifndef ARCHETYPE_MANAGER_H
#define ARCHETYPE_MANAGER_H

#include <unordered_map>
#include "Generic/Util/VLUI64.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Archetype.h"
#include <vector>

namespace Generic {
	namespace ECS {
		class ArchetypeManager
		{
		public:
			static int addEntity(int entityTypeId);
			static bool removeEntity(int entityId);

		private:
			static std::unordered_map<int, Archetype> archetypes;
			static std::unordered_map<int, std::vector<int>> componentTypeIdsList;
			static Util::NameAllocator typeIDsAllocator;
			static Util::NameAllocator entityIDsAllocator;
			static std::unordered_map<int, std::pair<int, int>> entityLocations;
		};
	}
}

#endif 