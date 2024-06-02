#include "Generic/ECS/SystemManager.h"
#include "Generic/ECS/EntityManager.h"
#include "Generic/Util/VLUI64.h"
#include <iostream>
#include <cmath>

using namespace Generic::ECS;

class Renderer : public System { virtual void init() {} };
class glRenderer : public Renderer { virtual void init() {} };
class Physics : public System{ virtual void init() {} };

int main()
{
	SystemManager::addSystem<Renderer>();
	SystemManager::addImpl<Renderer>();
	SystemManager::loadSystem("Renderer", "Renderer");
	Generic::Util::VLUI64 a;
	a.set(0);
	EntityManager::addEntity<Renderer, glRenderer, Physics>();
	auto vlui1 = EntityManager::entityTypeMask(EntityManager::entityTypeId<Renderer, glRenderer, Physics>());
	auto vlui2 = EntityManager::entityTypeMask<Renderer, glRenderer, Physics>();
	return 0;
}