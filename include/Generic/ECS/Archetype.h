#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include <unordered_map>
#include <vector>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"

namespace Generic {
	namespace ECS {
		class Archetype
		{
		public:
			Archetype() : id(0) {

			}
			Archetype(int _id) : id(_id) {

			}
			int addEntity(std::vector<int> componentTypeIdArray);

		private:
			const int id;
			static const int maxEntityCountPerArchetype = 20;
			Util::NameAllocator entityIdAllocator = Util::NameAllocator::NameAllocator(maxEntityCountPerArchetype);
			std::unordered_map<int, std::vector<Component*>> entities;
		};
	}
}

#endif 