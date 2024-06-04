#ifndef NAME_ALLOCATOR_H
#define NAME_ALLOCATOR_H

#include <unordered_map>

namespace Generic {
	class NameAllocator
	{
	public:

		NameAllocator() : maxCount(5) {

		}

		NameAllocator(int _maxCount) : maxCount(_maxCount)
		{

		}

		int getName();
		void returnName(int name);
		bool isReserved(int name);
		void setMaxCount(int maxCount);

	private:
		int maxCount;
		int firstUnusedName = 0;
		std::unordered_map<int, int> restoredNames;
		std::unordered_map<int, int> allocatedNames;
	};
}

#endif 