#include "Generic/ECS/SystemManager.h"
#include "Generic/ECS/EntityManager.h"
#include "Generic/ECS/ComponentManager.h"
#include "Generic/Util/VLUI64.h"
#include <iostream>
#include <cmath>

using namespace Generic;

class Renderer : public Component {public: int var1 = 5; };
class glRenderer : public Component {   };
class Physics : public Component {   };
class Shader {};
class Mesh{};

int main()
{
	SystemManager::addSystem<Renderer>();
	SystemManager::addImpl<Renderer>();
	SystemManager::loadSystem("Renderer", "Renderer");
	ComponentManager::registerComponentType<Renderer>();
	ComponentManager::registerComponentType<glRenderer>();
	ComponentManager::registerComponentType<Physics>();
	int entityTypeId = EntityManager::addEntityType<Renderer, glRenderer, Physics>();
	ComponentManager::alloc();
	int entity1 = EntityManager::addEntity<Physics, Renderer, glRenderer>();
	EntityManager::addEntity<Physics, glRenderer>();
	EntityManager::setEntityTypeName(entityTypeId, "basic");
	EntityManager::addEntity<Renderer, glRenderer>();
	EntityManager::addEntity<Physics>();
	EntityManager::addEntity<glRenderer>();
	EntityManager::addEntity<Renderer>();
	Mesh* c = EntityManager::getComponent<Mesh>(entity1);
	return 0;
}