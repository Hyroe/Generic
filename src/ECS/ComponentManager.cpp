#include "Generic/ECS/ComponentManager.h"

int Generic::ECS::ComponentManager::componentTypeIDCount = 0;;
std::unordered_map<int, Generic::ECS::PoolAllocator<Component>> Generic::ECS::ComponentManager::poolAllocators;