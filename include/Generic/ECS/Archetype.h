#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include <unordered_map>
#include <map>
#include <vector>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Util/VLUI64.h"

namespace Generic {
	class Archetype
	{
	public:
		int addEntity(const int& entityTypeId, const VLUI64& entityTypeMask);
		bool removeEntity(const int& entityTypeId, const int& entityLocalId);
		void addLink(const VLUI64& mask, Archetype* archetype);

	private:
		static const int maxEntityCountPerArchetype = 20;
		NameAllocator entityIdAllocator = NameAllocator::NameAllocator(maxEntityCountPerArchetype);
		std::unordered_map<int, Component*[maxEntityCountPerArchetype]> entities;
		std::map<VLUI64, Archetype*> superArchetypes;
	};
}

#endif 