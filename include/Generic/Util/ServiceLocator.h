#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATIR_H

#include <unordered_map>
#include "Generic/Util/Service.h"

class ServiceLocator
{
public:
	template <typename ReturnType, typename ...Args>
	static ReturnType access(int service, int method, Args ...args) {
		return ServiceLocator::services[service].run<ReturnType, Args...>(method, args...);
	}

	template <typename ...Args>
	static void access(int service, int method, Args ...args) {
		ServiceLocator::services[service].run(method, args...);
	}

	static void access(int service, int method) {
		ServiceLocator::services[service].run(method);
	}

	static Service services[30];
};

#endif 