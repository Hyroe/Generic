#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Util/Util.h"
#include "Generic/Util/RTTI.h"
#include "Generic/ECS/EntityManager.h"


namespace Generic {

	class PoolAllocator {
	public:
		virtual Component* getComponent(const int&) = 0;
		virtual void alloc() = 0;
		virtual bool isEmpty() = 0;
		virtual void returnComponent(const int&, Component*) = 0;
		virtual void returnComponentWithCopy(const int&, Component*) = 0;
	};

	template <typename T>
	class PoolAllocatorTemplate : public PoolAllocator
	{
	public:
		virtual Component* getComponent(const int& entityTypeId) {
			int block = blocks[entityTypeId];
			int index = componentIndicesAllocator[block].getName();
			assertNoAbort([&index, this]()->bool {return index < blockSize; }, "PoolAllocator :: getComponent :: component index out of bounds"
				" you may increase block size for component " + GRTTI::typeName<T>() + " if required.");
			Component* c = reinterpret_cast<Component*>(&data[block][index]);
			reservedComponentIndices[block][c] = index;
			return c;
		}

		virtual void alloc() {
			int blockCount = EntityManager::entityTypeLists[GRTTI::typeId<T>()].size();

			for (int i = 0; i < blockCount; i++)
			{
				data.push_back(std::vector<T>());
				for (int a = 0; a < blockSize; a++)
				{
					data[i].push_back(T());
				}
				for (int i = 0; i < blockCount; i++)
				{
					blocks[EntityManager::entityTypeLists[GRTTI::typeId<T>()][i]] = i;
				}
				for (int i = 0; i < blockCount; i++)
				{
					componentIndicesAllocator[EntityManager::entityTypeLists[GRTTI::typeId<T>()][i]] =
						NameAllocator(blockSize);
				}
			}
		}

		virtual bool isEmpty() {
			return data.size() == 0;
		}

		virtual void returnComponent(const int& entityTypeId, Component* c) {
			int componentBlock = blocks[entityTypeId];
			int componentIndex = reservedComponentIndices[componentBlock][c];
			int lastComponentIndex = componentIndicesAllocator[componentBlock].lastNameReserved();
			componentIndicesAllocator[componentBlock].returnName(componentIndex);
			reservedComponentIndices[componentBlock].erase(c);
		}

		virtual void returnComponentWithCopy(const int& entityTypeId, Component* c) {
			int componentBlock = blocks[entityTypeId];
			int componentIndex = reservedComponentIndices[componentBlock][c];
			int lastComponentIndex = componentIndicesAllocator[componentBlock].lastNameReserved();
			if (componentIndex != lastComponentIndex)
			{
				data[componentBlock][componentIndex] = data[componentBlock][lastComponentIndex];
				componentIndicesAllocator[componentBlock].returnName(lastComponentIndex);
				reservedComponentIndices[componentBlock].erase((--reservedComponentIndices[componentBlock].end())->first);
			}
			else
			{
				componentIndicesAllocator[componentBlock].returnName(componentIndex);
				reservedComponentIndices[componentBlock].erase(c);
			}
		}

	private:
		static int blockCount;
		static const int blockSize = 16;
		std::vector<std::vector<T>> data;
		std::unordered_map<int, int> blocks;
		std::unordered_map<int, NameAllocator> componentIndicesAllocator;
		std::unordered_map<int, std::unordered_map<Component*, int>> reservedComponentIndices;
	};
}

#endif 