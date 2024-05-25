#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class Logger
{
public:
	static void logError(std::string&& err) {
		std::cerr << err << "\n";
	}
};

#endif 