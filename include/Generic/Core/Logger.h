#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

namespace Generic {
	class Logger
	{
	public:
		static void logError(std::string& err) {
			std::cerr << "error : " + err + "\n";
		}
	};
}

#endif 