#include "Generic/ECS/ComponentManager.h"

int Generic::ComponentManager::componentTypeIDCount = 0;;
std::unordered_map<int, std::unique_ptr<Generic::PoolAllocator>> Generic::ComponentManager::poolAllocators;