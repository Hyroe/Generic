#ifndef UTIL
#define UTIL

#include <functional>
#include <string>
#include <any>
#include "Generic/Core/Logger.h"

namespace Generic {
	namespace Util {
		inline void assertNoAbort(bool expression, std::string errorString) {
		#ifndef NDEBUG
			if (!expression) {
				Core::Logger::logError(std::move(errorString));
			}
		#endif
		}
	}
}

#endif 