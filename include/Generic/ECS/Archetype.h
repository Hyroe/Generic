#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include <unordered_map>
#include <map>
#include <vector>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Util/VLUI64.h"
#include "Generic/Util/RTTI.h"

namespace Generic {
	class Archetype
	{
	public:
		int addEntity(const int& entityTypeId, const VLUI64& entityTypeMask);
		bool removeEntity(const int& entityTypeId, const int& entityLocalId);
		void addLink(const VLUI64& mask, Archetype* archetype);
		Component* getComponent(const int& entityId, const int& componentTypeId, std::string&&);

		template <typename T>
		Component* getComponent(const int& entityId)
		{
			assertNoAbort([this]()->bool {return entities.find(GRTTI::typeId<T>()) != entities.end(); },
				"Archetype :: getComponent :: component " + GRTTI::typeId<T>() + " not found in archetype");
			return entities[GRTTI::typeId<T>()][entityId];
		}

	private:
		static const int maxEntityCountPerArchetype = 20;
		NameAllocator entityIdAllocator = NameAllocator(maxEntityCountPerArchetype);
		std::unordered_map<int, Component*[maxEntityCountPerArchetype]> entities;
		std::map<VLUI64, Archetype*> superArchetypes;
	};
}

#endif 