#include "Generic/ECS/SystemManager.h"
#include <utility>

void Generic::ECS::SystemManager::loadSystem(std::string&& system, std::string&& impl) {
	if (systems.find(system) == systems.end())
	{
		Logger::logError("no matching system for : " + system);
		return;
	}
	if (implementations.find(impl) == implementations.end())
	{
		Logger::logError("no matching system for : " + impl);
		return;
	}

	if (validityChecks[system](implementations[impl].get()))
		systems[system] = impl;
	else
		Logger::logError(impl + " is not a " + system);
}

void Generic::ECS::SystemManager::runSystem(std::string&& sys) {
	if (systems.find(sys) == systems.end())
	{
		Logger::logError("no matching system for : " + sys);
		return;
	}
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

void Generic::ECS::SystemManager::setExecutionOrder(std::string&& sys, unsigned int order) {
	if (systems.find(sys) == systems.end())
	{
		Logger::logError("no matching system for : " + sys);
		return;
	}
	if (runningSystems.find(systemExecutionOrder[sys]) == runningSystems.end())
	{
		Logger::logError("system : " + sys + " not currently running");
		return;
	}
	if (runningSystems.find(order) == runningSystems.end())
	{
		Logger::logError("specified order out of bounds");
		return;
	}
	if (runningSystems[order] == sys)
		return;
	swapExecutionOrder(std::move(sys), std::move(runningSystems[order]));
}

void Generic::ECS::SystemManager::swapExecutionOrder(std::string&& sys1, std::string&& sys2) {
	if (systems.find(sys1) == systems.end())
	{
		Logger::logError("no matching system for : " + sys1);
		return;
	}
	if (systems.find(sys2) == systems.end())
	{
		Logger::logError("no matching system for : " + sys2);
		return;
	}
	if (runningSystems.find(systemExecutionOrder[sys1]) == runningSystems.end())
	{
		Logger::logError("system : " + sys1 + " not currently running");
		return;
	}
	if (runningSystems.find(systemExecutionOrder[sys2]) == runningSystems.end())
	{
		Logger::logError("system : " + sys2 + " not currently running");
		return;
	}

	runningSystems[systemExecutionOrder[sys1]] = sys2;
	runningSystems[systemExecutionOrder[sys2]] = sys1;

	int order = systemExecutionOrder[sys1];
	systemExecutionOrder[sys1] = systemExecutionOrder[sys2];
	systemExecutionOrder[sys2] = order;
}

void Generic::ECS::SystemManager::stopSystem(std::string&& sys) {
	if (systems.find(sys) == systems.end())
	{
		Logger::logError("no matching system for : " + sys);
		return;
	}
	if (runningSystems.find(systemExecutionOrder[sys]) == runningSystems.end())
	{
		Logger::logError("system : " + sys + " not currently running");
		return;
	}
	runningSystems.erase(systemExecutionOrder[sys]);
}

std::unordered_map<std::string, unsigned int> Generic::ECS::SystemManager::systemExecutionOrder;
std::unordered_map<unsigned int, std::string> Generic::ECS::SystemManager::runningSystems;
std::unordered_map<std::string, std::string> Generic::ECS::SystemManager::systems;
std::unordered_map<std::string, std::unique_ptr<Generic::ECS::System>> Generic::ECS::SystemManager::implementations;
std::unordered_map<std::string, std::function<bool(Generic::ECS::System*)>> Generic::ECS::SystemManager::validityChecks;