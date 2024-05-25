#include "Generic/ECS/ComponentManager.h"

Generic::Util::NameAllocator Generic::ECS::ComponentManager::typeIDsAllocator = Generic::Util::NameAllocator(20);
std::unordered_map<std::string, unsigned int> Generic::ECS::ComponentManager::typeIDs;