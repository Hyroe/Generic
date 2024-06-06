#ifndef SYSTEM_H
#define SYSTEM_H

#include <functional>

namespace Generic {
	class System
	{
		virtual void init() = 0;

		template <typename T, typename ...Types>
		void runEntityProc(std::function<T(Types...)> f) {

		}
	};
}

#endif