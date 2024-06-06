#include "Generic/ECS/SystemManager.h"
#include "Generic/ECS/EntityManager.h"
#include "Generic/ECS/ComponentManager.h"
#include "Generic/Util/VLUI64.h"
#include <iostream>
#include <cmath>

using namespace Generic;

class Renderer : public Component {   };
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
	std::cout << EntityManager::addEntityType<Renderer, glRenderer>() << std::endl;
	std::cout << EntityManager::addEntityType<Renderer>() << std::endl;
	std::cout << EntityManager::addEntityType<glRenderer>() << std::endl;
	std::cout << EntityManager::addEntityType<Renderer, glRenderer, Physics>() << std::endl;
	std::cout << EntityManager::addEntityType<Renderer, Physics>() << std::endl;
	std::cout << EntityManager::addEntityType<glRenderer, Physics>() << std::endl;
	std::cout << EntityManager::addEntityType<Physics>() << std::endl;
	ComponentManager::alloc();
	return 0;
}