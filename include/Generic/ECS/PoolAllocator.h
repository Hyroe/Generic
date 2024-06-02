#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include "Generic/ECS/Component.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/Core/Logger.h"

namespace Generic {
	namespace ECS {
		template <typename T>
		class PoolAllocator
		{
		public:
			template <typename N>
			void registerFactory() {
				factory = []()-> std::unique_ptr<T> {
					return std::make_unique<N>();
				};
			}

			Component* getComponent(int block) {
				if (block >= blockCount)
				{
					Core::Logger::logError("block out of bounds");
					return nullptr;
				}
				int index = componentIndicesAllocator.at(block).getName();
				return data[block][index];
			}

			void alloc() {
				data.shrink_to_fit();
				data.reserve(blockCount * blockSize * sizeof(T));
				for (int i = 0; i < blockCount; i++)
				{
					componentIndicesAllocator.emplace({i, blockSize});
				}
			}

		private:
			static const int blockSize = 32;
			const int blockCount = 5;
			std::function<std::unique_ptr<T>()> factory;
			std::vector<std::vector<T*>> data;
			std::unordered_map<int, Util::NameAllocator> componentIndicesAllocator;
		};
	}
}

#endif 