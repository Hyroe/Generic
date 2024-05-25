#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include "Generic/Core/Logger.h"
#include "Generic/Util/RTTI.h"
#include "System.h"

namespace Generic {
	namespace ECS {
		class SystemManager
		{
		public:
			template <typename T>
			static void addSystem() {
				systems[GRTTI::typeName<T>()] = "";
				addValidityCheck<T>();
			}

			template <typename T>
			static void removeSystem() {
				if (systems.find(GRTTI::typeName<T>()) == systems.end())
				{
					Logger::logError("no matching system for : " + GRTTI::typeName<T>());
					return;
				}
				systems.erase(GRTTI::typeName<T>());
			}

			static void loadSystem(std::string&& system, std::string&& impl);

			template <typename T>
			static void addImpl() {
				T sys = T();
				if (!dynamic_cast<System*>(&sys))
				{
					Logger::logError(GRTTI::typeName<T>() + " is not a System");
					return;
				}
				implementations[GRTTI::typeName<T>()] = std::make_unique<T>();
			}

			template <typename T>
			static void removeImpl() {
				if (implementations.find(GRTTI::typeName<T>()) == implementations.end())
				{
					Logger::logError("no matching implementation for : " + GRTTI::typeName<T>());
					return;
				}
				implementations.erase(GRTTI::typeName<T>());
			}

			static void runSystem(std::string&& sys);
			static void stopSystem(std::string&& sys);
			static void setExecutionOrder(std::string&& sys, unsigned int order);

		private:
			template <typename T>
			static void addValidityCheck() {
				validityChecks[GRTTI::typeName<T>()] = [](System* sys) -> bool {
					if (dynamic_cast<T*>(sys))
						return true;
					return false;
				};
			}

			static void swapExecutionOrder(std::string&& sys1, std::string&& sys2);

			static std::unordered_map<std::string, unsigned int> systemExecutionOrder;
			static std::unordered_map<unsigned int, std::string> runningSystems;
			static std::unordered_map<std::string, std::string> systems;
			static std::unordered_map<std::string, std::unique_ptr<System>> implementations;
			static std::unordered_map<std::string, std::function<bool(System*)>> validityChecks;
		};
	}
}

#endif 