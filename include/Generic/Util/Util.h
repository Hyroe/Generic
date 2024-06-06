#ifndef UTIL
#define UTIL

#include <functional>
#include <string>
#include <any>
#include <utility>
#include "Generic/Core/Logger.h"
#include "Generic/Util/RTTI.h"

namespace Generic {
	inline void assertNoAbort(std::function<bool()> condition, std::string&& msg) {
#ifndef NDEBUG
		if (!condition()) {
			Logger::logError(msg);
		}
#endif
	}

	template <typename T, typename ...Types>
	void iterateTypeIds(std::function<void(const int& typeId)> &&f) {
		f(GRTTI::typeId<T>());
		if constexpr (sizeof...(Types) != 0)
			iterateTypeIds<Types...>(std::move(f));
	}

}

#endif 