#include "Generic/ECS/SystemManager.h"
#include "Generic/Util/Util.h"

void Generic::SystemManager::loadSystem(std::string&& system, std::string&& impl) {
	assertNoAbort([&system]()->bool{return systems.find(system) != systems.end(); },
		"SystemManager  :: loadSystem :: no mathcing system for" + system);
	assertNoAbort([&impl]()->bool {return implementations.find(impl) != implementations.end(); },
		"SystemManager  :: loadSystem :: no mathcing implementation for" + impl);
	assertNoAbort([&, system, impl]()->bool {return validityChecks[system](implementations[impl].get()); },
		"SystemManager :: loadSystem :: " + impl + " is not a system");

	systems[system] = impl;
}

void Generic::SystemManager::runSystem(std::string&& sys) {
	assertNoAbort([&sys]()->bool {return systems.find(sys) != systems.end(); }, 
		"SystemManager :: runSystems :: no mathcing System for " + sys);
	switch (runningSystems.size())
	{
	case 0:
		runningSystems[0] = sys;
		systemExecutionOrder[sys] = 0;
		break;
	default:
		int order = runningSystems.end()->first + 1;
		runningSystems[order] = sys;
		systemExecutionOrder[sys] = order;
		break;
	}
}

void Generic::SystemManager::setExecutionOrder(std::string&& sys, unsigned int order) {
	assertNoAbort([&sys]()->bool {return systems.find(sys) != systems.end(); },
		"SystemManager :: setExecutionOrder :: no mathcing System for " + sys);
	assertNoAbort([&sys]()->bool {return runningSystems.find(systemExecutionOrder[sys]) != runningSystems.end(); },
		"SystemManager :: setExecutionOrder :: system : " + sys + " not currently running");
	assertNoAbort([&order]()->bool {return runningSystems.find(order) == runningSystems.end(); },
		"SystemManager :: setExecutionOrder :: " + sys + " :: specified order out of bounds");

	if (runningSystems[order] == sys)
		return;

	swapExecutionOrder(std::move(sys), std::move(runningSystems[order]));
}

void Generic::SystemManager::swapExecutionOrder(std::string&& sys1, std::string&& sys2) {
	assertNoAbort([&sys1]()->bool {return systems.find(sys1) != systems.end(); },
		"SystemManager :: swapExecutionOrder :: no matching system for " + sys1);
	assertNoAbort([&sys2]()->bool {return systems.find(sys2) != systems.end(); },
		"SystemManager :: swapExecutionOrder :: no matching system for " + sys2);
	assertNoAbort([&sys1]()->bool {return runningSystems.find(systemExecutionOrder[sys1]) != runningSystems.end(); },
		"SystemManager :: swapExecutionOrder :: system " + sys1 + " not currently running");
	assertNoAbort([&sys2]()->bool {return runningSystems.find(systemExecutionOrder[sys2]) != runningSystems.end(); },
		"SystemManager :: swapExecutionOrder :: system " + sys2 + " not currently running");

	runningSystems[systemExecutionOrder[sys1]] = sys2;
	runningSystems[systemExecutionOrder[sys2]] = sys1;

	int order = systemExecutionOrder[sys1];
	systemExecutionOrder[sys1] = systemExecutionOrder[sys2];
	systemExecutionOrder[sys2] = order;
}

void Generic::SystemManager::stopSystem(std::string&& sys) {
	assertNoAbort([&sys]()->bool {return systems.find(sys) != systems.end(); },
		"SystemManager :: swapExecutionOrder :: no matching system for " + sys);
	assertNoAbort([&sys]()->bool {return runningSystems.find(systemExecutionOrder[sys]) != runningSystems.end(); },
		"SystemManager :: swapExecutionOrder :: system " + sys + " not currently running");
	runningSystems.erase(systemExecutionOrder[sys]);
}

std::unordered_map<std::string, unsigned int> Generic::SystemManager::systemExecutionOrder;
std::unordered_map<unsigned int, std::string> Generic::SystemManager::runningSystems;
std::unordered_map<std::string, std::string> Generic::SystemManager::systems;
std::unordered_map<std::string, std::unique_ptr<Generic::System>> Generic::SystemManager::implementations;
std::unordered_map<std::string, std::function<bool(Generic::System*)>> Generic::SystemManager::validityChecks;