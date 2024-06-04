#ifndef UTIL
#define UTIL

#include <functional>
#include <string>
#include <any>
#include "Generic/Core/Logger.h"

namespace Generic {
	inline void assertNoAbort(std::function<bool()> condition, std::string&& msg) {
#ifndef NDEBUG
		if (!condition()) {
			Logger::logError(msg);
		}
#endif
	}
}

#endif 