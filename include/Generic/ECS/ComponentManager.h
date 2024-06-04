#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <string>
#include <cassert>
#include "Generic/Util/RTTI.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Component.h"
#include "Generic/Core/Logger.h"
#include "Generic/ECS/PoolAllocator.h"
#include "Generic/Util/Util.h"

namespace Generic {
	class ComponentManager {
	public:
		static void alloc() {
			for (auto &poolAllocator : poolAllocators)
			{
				poolAllocator.second.get()->alloc();
			}
		}

		template <typename T>
		static void registerComponentType() {
			assertNoAbort([]()->bool {return std::is_base_of<Component, T>::value; }, "ComponentManager :: registerComponentType :: " + GRTTI::typeName<T>() + " is not a component type");
			poolAllocators[typeId<T>()] = std::make_unique<PoolAllocatorTemplate<T>>();
		}

		template <typename T>
		static VLUI64 typeMask() {
			return GRTTI::typeMask(typeId<T>());
		}

		template <typename T>
		static int typeId() {
			static int componentTypeID = componentTypeIDCount++;
			return componentTypeID;
		}

		static Component* getComponent(int entityTypeId, int componentTypeId) {
			assertNoAbort([&componentTypeId]()->bool {return componentTypeId < maxComponentTypeCount; },
				"ComponentManager :: getComponent :: component type id out of bounds"
				" you may increase maximum component type count if required.");
			assert(!poolAllocators[componentTypeId].get()->isEmpty() && "ComponentManager :: getComponent :: pool allocator empty,"
			" ensure alloc is called after all component types registration");
			Component* c = poolAllocators[componentTypeId].get()->getComponent(entityTypeId);
			c->reset();
			return c;
		}

	private:
		static const int maxComponentTypeCount = 5;
		static int componentTypeIDCount;
		static std::unordered_map<int, std::unique_ptr<PoolAllocator>> poolAllocators;
	};
}

#endif 