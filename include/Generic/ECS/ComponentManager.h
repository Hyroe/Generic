#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include "Generic/Util/RTTI.h"
#include "Generic/Util/NameAllocator.h"
#include "Generic/ECS/Component.h"
#include "Generic/Core/Logger.h"

namespace Generic {
	namespace ECS {
		class ComponentManager {
		public:
			template <typename T>
			static void registerComponentType() {
				if constexpr (std::is_base_of<Component, T>::value)
				{
					typeIDs[GRTTI::typeName<T>()] = typeIDsAllocator.getName();
				}
			}

			template <typename T>
			static Util::VLUI64 typeMask() {
				if (typeIDs.find(GRTTI::typeName<T>()) == typeIDs.end())
				{
					Logger::logError("component type " + GRTTI::typeName<T>() " not found");
					return Util::VLUI64();
				}
				return GRTTI::typeMask(typeIDs.at(GRTTI::typeName<T>()));
			}

		private:
			static Util::NameAllocator typeIDsAllocator;
			static std::unordered_map<std::string, unsigned int> typeIDs;
		};
	}
}

#endif 