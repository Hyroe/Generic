#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

namespace Generic {
	namespace Core {
		class Logger
		{
		public:
			static void logError(std::string&& err) {
				std::cerr << err << "\n";
			}
		};
	}
}

#endif 