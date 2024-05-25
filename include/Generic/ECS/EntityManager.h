#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Generic/Util/VLUI64.h"

namespace Generic{
	namespace ECS {
		class EntityManager
		{
		public:
			static int addEntity(Util::VLUI64 typeMask);
		};
	}
}

#endif 