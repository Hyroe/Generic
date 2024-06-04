#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Util/Util.h"

const int getInt();

namespace Generic {

	class PoolAllocator {
	public:
		virtual Component* getComponent(int) = 0;
		virtual void alloc() = 0;
		virtual bool isEmpty() = 0;
	};

	template <typename T>
	class PoolAllocatorTemplate : public PoolAllocator
	{
	public:
		Component* getComponent(int entityTypeId) {
			try {
				int block = blocks.try_emplace(entityTypeId, blockIndicesAllocator.getName()).first->second;
				assertNoAbort([&block, this]()->bool {return block < blockCount; }, "PoolAllocator :: getComponent :: block index out of bounds,"
					" you may increase block count for component " + GRTTI::typeName<T>() + " if required.");
				int index = componentIndicesAllocator.try_emplace(block, blockSize).first->second.getName();
				assertNoAbort([&index, this]()->bool {return index < blockSize; }, "PoolAllocator :: getComponent :: component index out of bounds"
					" you may increase block size for component " + GRTTI::typeName<T>() + " if required.");
				return reinterpret_cast<Component*>(data[block][index].get());
			}
			catch (std::exception& error) {

			}
		}

		void alloc() {
			for (int i = 0; i < blockCount; i++)
			{
				data.push_back(std::vector<std::unique_ptr<T>>());
				for (int a = 0; a < blockSize; a++)
				{
					data[i].push_back(factory());
				}
				//componentIndicesAllocator[i].setMaxCount(blockSize);
			}
		}

		bool isEmpty() {
			return data.size() == 0;
		}

	private:
		static const int blockSize = 16;
		static const int blockCount = 5;
		std::function<std::unique_ptr<T>()> factory = []()->std::unique_ptr<T> {return std::make_unique<T>(); };
		std::vector<std::vector<std::unique_ptr<T>>> data;
		std::unordered_map<int, int> blocks;
		std::unordered_map<int, NameAllocator> componentIndicesAllocator;
		NameAllocator blockIndicesAllocator = NameAllocator(blockCount);
	};
}

#endif 