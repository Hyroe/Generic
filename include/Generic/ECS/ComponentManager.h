#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include "Generic/Util/RTTI.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Component.h"
#include "Generic/Core/Logger.h"
#include "Generic/ECS/PoolAllocator.h"
#include "Generic/Util/Util.h"

namespace Generic {
	namespace ECS {
		class ComponentManager {
		public:
			template <typename T>
			static Util::VLUI64 typeMask() {
				return GRTTI::typeMask(typeId<T>());
			}

			template <typename T>
			static int typeId() {
				Util::assertNoAbort(std::is_base_of<Component, T>::value, GRTTI::typeName<T>() + " is not a component type");
				static int componentTypeID = componentTypeIDCount++;
				return componentTypeID;
			}

			static Component* getComponent(int entityTypeId, int componentTypeId) {
				if (poolAllocators.find(componentTypeId) == poolAllocators.end())
				{
					Core::Logger::logError("component type not registered");
					return nullptr;
				}
				poolAllocators[componentTypeId].getComponent(entityTypeId);
			}

		private:
			static int componentTypeIDCount;
			static std::unordered_map<int, PoolAllocator<Component>> poolAllocators;
		};
	}
}

#endif 