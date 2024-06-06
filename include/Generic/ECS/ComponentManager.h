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
				poolAllocator.second->alloc();
			}
		}

		template <typename T>
		static void registerComponentType() {
			assertNoAbort([]()->bool {return std::is_base_of<Component, T>::value; }, 
				"ComponentManager :: registerComponentType :: " + GRTTI::typeName<T>() + " doesnt inherit from Component");
			componentTypeSizes[GRTTI::typeId<T>()] = sizeof(T);
			poolAllocators[GRTTI::typeId<T>()] = std::make_unique<PoolAllocatorTemplate<T>>();
		}

		static Component* getComponent(int entityTypeId, int componentTypeId) {
			assert(!poolAllocators[componentTypeId]->isEmpty() && "ComponentManager :: getComponent :: pool empty,"
			" ensure ComponentManager::alloc is called right after all component types registrations");
			Component* c = poolAllocators[componentTypeId]->getComponent(entityTypeId);
			c->reset();
			return c;
		}

		static void returnComponent(int entityTypeId, int componentTypeId, Component* c) {
			poolAllocators[componentTypeId]->returnComponent(entityTypeId, c);
		}

		static void returnComponentWithCopy(int entityTypeId, int componentTypeId, Component* c) {
			poolAllocators[componentTypeId]->returnComponentWithCopy(entityTypeId, c);
		}

		static std::unordered_map<int, int> componentTypeSizes;

	private:
		static int componentTypeIDCount;
		static std::unordered_map<int, std::unique_ptr<PoolAllocator>> poolAllocators;
	};
}

#endif 